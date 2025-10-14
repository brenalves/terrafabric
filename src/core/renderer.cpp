#include "renderer.h"

Renderer* Renderer::_instance = nullptr;

Renderer::Renderer()
{
    if(_instance != nullptr)
    {
        throw std::runtime_error("Renderer instance already exists!");
    }

    _instance = this;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, 800, 600);

    _uniformBuffer = new UniformBuffer(2 * sizeof(glm::mat4), 0);

    ResourceManager::loadShader("quad", "assets/shaders/quad.vert", "assets/shaders/quad.frag");
    ResourceManager::loadShader("chunk", "assets/shaders/chunk.vert", "assets/shaders/chunk.frag");

    Texture2D* atlas = ResourceManager::loadTexture("atlas");
    atlas->loadFromFile("assets/textures/atlas.png");

    Texture2D* crosshair = ResourceManager::loadTexture("crosshair");
    crosshair->loadFromFile("assets/textures/crosshair.png");

    _drawMode = DrawMode::FILL;

    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
    delete _uniformBuffer;

    _instance = nullptr;
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::beginFrame(Transform &cameraTransform, Camera &camera)
{
    glm::mat4 view = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraTransform.forward, cameraTransform.up);
    glm::mat4 projection = camera.getProjectionMatrix();

    _uniformBuffer->setSubData(0, sizeof(glm::mat4), &projection);
    _uniformBuffer->setSubData(sizeof(glm::mat4), sizeof(glm::mat4), &view);
}

void Renderer::drawQuad(Transform &transform, Mesh* mesh)
{
    Shader* shader = ResourceManager::getShader("quad");

    shader->bind();

    glm::mat4 model = transform.getModelMatrix();
    shader->setUniformMatrix4fv("u_Model", glm::value_ptr(model));

    mesh->VAO.bind();
    mesh->VBO.bind();
    mesh->EBO.bind();

    glDrawElements(GL_TRIANGLES, mesh->EBO.getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::drawChunk(glm::vec3 position, Mesh *mesh)
{
    Shader* shader = ResourceManager::getShader("chunk");

    shader->bind();

    Texture2D* atlas = ResourceManager::getTexture("atlas");
    atlas->bind(0);
    shader->setUniform1i("u_Texture", 0); // Texture unit 0

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    shader->setUniformMatrix4fv("u_Model", glm::value_ptr(model));

    mesh->VAO.bind();
    mesh->VBO.bind();
    mesh->EBO.bind();

    glDrawElements(GL_TRIANGLES, mesh->EBO.getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::setDrawMode(DrawMode mode)
{
    _drawMode = mode;
    glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(mode));
}

void Renderer::onResize(int width, int height)
{
    glViewport(0, 0, width, height);
}
