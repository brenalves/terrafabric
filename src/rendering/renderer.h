#pragma once

#include <glad/glad.h>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rendering/buffer.h"
#include "components/transform.h"
#include "components/camera.h"
#include "components/mesh.h"
#include "core/resourcemanager.h"

enum class DrawMode
{
    FILL = GL_FILL,
    LINE = GL_LINE,
    POINT = GL_POINT
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear();
    void beginFrame(Transform& cameraTransform, Camera& camera);
    
    void drawChunk(glm::vec3 position, Mesh* mesh);
    void drawSprite(Transform& transform, Texture2D* texture);
    void drawRay(glm::vec3 origin, glm::vec3 direction, float length, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f));

    void setDrawMode(DrawMode mode);

    void onResize(int width, int height);

    inline DrawMode getDrawMode() const { return _drawMode; }

    inline static Renderer* getInstance() { return _instance; }

private:
    DrawMode _drawMode;

    UniformBuffer* _uniformBuffer;

    static Renderer* _instance;
};