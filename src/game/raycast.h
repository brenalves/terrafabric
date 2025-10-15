#pragma once

#include <glm/glm.hpp>

#include "world.h"
#include "block.h"

struct RaycastHit
{
    glm::vec3 position;
    glm::vec3 normal;
    float distance;
    BlockType blockType;
};

class Raycast
{
public:
    // DDA algorithm for raycasting in a voxel grid
    // Returns true if a block was hit, false otherwise
    // If a block is hit, hitInfo is populated with details about the hit
    static bool intersectRayWithBlocks(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, float maxDistance, RaycastHit* hitInfo);
};