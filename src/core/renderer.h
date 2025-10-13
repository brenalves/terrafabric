#pragma once

#include <glad/glad.h>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "rendering/buffer.h"
#include "components/transform.h"
#include "components/camera.h"
#include "components/mesh.h"
#include "core/resourcemanager.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear();
    void beginFrame(Transform& cameraTransform, Camera& camera);
    void drawQuad(Transform& transform, Mesh* mesh);

    void onResize(int width, int height);

    inline static Renderer* getInstance() { return _instance; }

private:
    UniformBuffer* _uniformBuffer;

    static Renderer* _instance;
};