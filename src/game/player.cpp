#include "player.h"

Player::Player()
{
    _speed = 15.0f;
}

void Player::update()
{
    Input* input = Input::getInstance();
    Timer* timer = Timer::getInstance();

    // Update player transform and camera
    _transform.updateVectors();

    glm::vec3 movementDirection(0.0f);


    if (input->isKeyDown(GLFW_KEY_W))
        movementDirection += _transform.forward;
    if (input->isKeyDown(GLFW_KEY_S))
        movementDirection -= _transform.forward;

    movementDirection.y = 0.0f; // Prevent moving up/down when looking up/down

    if (input->isKeyDown(GLFW_KEY_A))
        movementDirection -= _transform.right;
    if (input->isKeyDown(GLFW_KEY_D))
        movementDirection += _transform.right;

    if (glm::length(movementDirection) != 0.0f)
        movementDirection = glm::normalize(movementDirection);

    _transform.position += movementDirection * _speed * timer->getDeltaTime();
}
