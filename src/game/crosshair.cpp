#include "crosshair.h"

Crosshair::Crosshair()
{
    _transform.position = glm::vec3(400.0f, 300.0f, 0.0f);
    _transform.scale = glm::vec3(32.0f, 32.0f, 1.0f); // Size in pixels

    _texture = ResourceManager::loadTexture("crosshair");
    _texture->loadFromFile("assets/textures/crosshair.png");
}

void Crosshair::update()
{
    _transform.updateVectors();
}
