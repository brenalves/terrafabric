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

void Renderer::onResize(int width, int height)
{
    glViewport(0, 0, width, height);
}
