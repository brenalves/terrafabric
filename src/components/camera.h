#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera
{
    float fov = 60.0f;
    float aspectRatio = 4.0f / 3.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    glm::mat4 getProjectionMatrix() const
    {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }
};