#include "player.h"

Player::Player()
{
    _speed = 15.0f;
    _sensitivity = 0.1f;
}

void Player::update()
{
    Input *input = Input::getInstance();
    Timer *timer = Timer::getInstance();

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

    if(input->isKeyDown(GLFW_KEY_SPACE))
        movementDirection += glm::vec3(0.0f, 1.0f, 0.0f);
    if(input->isKeyDown(GLFW_KEY_LEFT_SHIFT))
        movementDirection -= glm::vec3(0.0f, 1.0f, 0.0f);

    if (glm::length(movementDirection) != 0.0f)
        movementDirection = glm::normalize(movementDirection);

    _transform.position += movementDirection * _speed * timer->getDeltaTime();

    if (input->getCursorMode() == DISABLED)
    {
        float mouseX = input->getMouseX();
        float mouseY = input->getMouseY();

        if (firstMouse)
        {
            lastX = mouseX;
            lastY = mouseY;
            firstMouse = false;
        }

        float xOffset = static_cast<float>(mouseX - lastX);
        float yOffset = static_cast<float>(lastY - mouseY); // reversed since y-coordinates go from bottom to top

        lastX = mouseX;
        lastY = mouseY;

        xOffset *= _sensitivity;
        yOffset *= _sensitivity;

        _transform.rotation.y += xOffset;
        _transform.rotation.x += yOffset;

        if (_transform.rotation.x > 89.0f)
            _transform.rotation.x = 89.0f;
        if (_transform.rotation.x < -89.0f)
            _transform.rotation.x = -89.0f;
    }
    else
    {
        firstMouse = true;
    }
}

void Player::onResize(int width, int height)
{
    _camera.aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}
