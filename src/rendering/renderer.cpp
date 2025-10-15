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
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _drawMode = DrawMode::FILL;

    _uniformBuffer = new UniformBuffer(3 * sizeof(glm::mat4), 0);
    glm::mat4 ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    _uniformBuffer->setSubData(2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(ortho));

    ResourceManager::loadShader("sprite", "assets/shaders/sprite.vert", "assets/shaders/sprite.frag");
    ResourceManager::loadShader("chunk", "assets/shaders/chunk.vert", "assets/shaders/chunk.frag");
    ResourceManager::loadShader("ray", "assets/shaders/ray.vert", "assets/shaders/ray.frag");

    Texture2D* atlas = ResourceManager::loadTexture("atlas");
    atlas->loadFromFile("assets/textures/atlas.png");

    float quadVertices[] = {
        // positions        // texture coords
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top-left
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top-right
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f  // bottom-left
    };
    unsigned int quadIndices[] = {
        0, 1, 2,
        2, 3, 0
    };
    BufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(2); // texture coords

    Mesh* quadMesh = ResourceManager::loadMesh("quad");
    quadMesh->VBO->setData(sizeof(quadVertices), quadVertices);
    quadMesh->EBO->setData(sizeof(quadIndices), quadIndices);
    quadMesh->VAO->addVertexBuffer(*quadMesh->VBO, layout);

    float rayVertices[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    BufferLayout rayLayout;
    rayLayout.push<float>(3); // position
    Mesh* rayMesh = ResourceManager::loadMesh("ray");
    rayMesh->VBO->setData(sizeof(rayVertices), rayVertices);
    rayMesh->VAO->addVertexBuffer(*rayMesh->VBO, rayLayout);
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

void Renderer::drawChunk(glm::vec3 position, Mesh *mesh)
{
    Shader* shader = ResourceManager::getShader("chunk");

    shader->bind();

    Texture2D* atlas = ResourceManager::getTexture("atlas");
    atlas->bind(0);
    shader->setUniform1i("u_Texture", 0); // Texture unit 0

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    shader->setUniformMatrix4fv("u_Model", glm::value_ptr(model));

    mesh->VAO->bind();
    mesh->VBO->bind();
    mesh->EBO->bind();

    glDrawElements(GL_TRIANGLES, mesh->EBO->getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::drawSprite(Transform &transform, Texture2D *texture)
{
    Shader* shader = ResourceManager::getShader("sprite");

    shader->bind();

    texture->bind(0);
    shader->setUniform1i("u_Texture", 0); // Texture unit 0

    shader->setUniformMatrix4fv("u_Model", glm::value_ptr(transform.getModelMatrix()));

    Mesh* quadMesh = ResourceManager::getMesh("quad");
    quadMesh->VAO->bind();
    quadMesh->VBO->bind();
    quadMesh->EBO->bind();

    glDrawElements(GL_TRIANGLES, quadMesh->EBO->getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::drawRay(glm::vec3 origin, glm::vec3 direction, float length, glm::vec3 color)
{
    Shader* shader = ResourceManager::getShader("ray");

    shader->bind();

    // Calculate the model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, origin);

    // Align the ray with the direction
    // I need to understand this better
    glm::vec3 dirNorm = glm::normalize(direction);
    float angle = acos(glm::dot(dirNorm, glm::vec3(0.0f, 0.0f, 1.0f)));
    glm::vec3 axis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), dirNorm);
    if(glm::length(axis) > 0.0001f) // Avoid NaN
        model = glm::rotate(model, angle, glm::normalize(axis));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, length));

    shader->setUniformMatrix4fv("u_Model", glm::value_ptr(model));
    shader->setUniform3fv("u_Color", glm::value_ptr(color));

    Mesh* rayMesh = ResourceManager::getMesh("ray");
    rayMesh->VAO->bind();

    glDrawArrays(GL_LINES, 0, 2);
}

void Renderer::setDrawMode(DrawMode mode)
{
    _drawMode = mode;
    glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(mode));
}

void Renderer::onResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glm::mat4 ortho = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    _uniformBuffer->setSubData(2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(ortho));
}
