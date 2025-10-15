#include "raycast.h"

bool Raycast::intersectRayWithBlocks(const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection, float maxDistance, RaycastHit *hitInfo)
{
	// DDA algorithm for voxel traversal
	glm::vec3 dir = glm::normalize(rayDirection);
	glm::ivec3 blockPos = glm::floor(rayOrigin);

	glm::vec3 tDelta = glm::vec3(
		std::abs(1.0f / dir.x),
		std::abs(1.0f / dir.y),
		std::abs(1.0f / dir.z)
	);

	glm::ivec3 step;
	glm::vec3 tMax;
	for (int i = 0; i < 3; ++i) {
		if (dir[i] > 0) {
			step[i] = 1;
			tMax[i] = (glm::floor(rayOrigin[i]) + 1.0f - rayOrigin[i]) * tDelta[i];
		} else if (dir[i] < 0) {
			step[i] = -1;
			tMax[i] = (rayOrigin[i] - glm::floor(rayOrigin[i])) * tDelta[i];
		} else {
			step[i] = 0;
			tMax[i] = std::numeric_limits<float>::max();
		}
	}

	float distance = 0.0f;
	while (distance < maxDistance) {
		// Check if blockPos contains a block (replace with your block query)
        Block block = World::getInstance()->getBlockAt(blockPos);
		if (block.type != BlockType::AIR) {
			hitInfo->position = glm::vec3(blockPos);
			hitInfo->distance = distance;
            hitInfo->blockType = block.type;
			// Optionally set hitInfo.normal
			return true;
		}

		// Step to next voxel
		if (tMax.x < tMax.y && tMax.x < tMax.z) {
			blockPos.x += step.x;
			distance = tMax.x;
			tMax.x += tDelta.x;
			hitInfo->normal = glm::vec3(-step.x, 0, 0);
		} else if (tMax.y < tMax.z) {
			blockPos.y += step.y;
			distance = tMax.y;
			tMax.y += tDelta.y;
			hitInfo->normal = glm::vec3(0, -step.y, 0);
		} else {
			blockPos.z += step.z;
			distance = tMax.z;
			tMax.z += tDelta.z;
			hitInfo->normal = glm::vec3(0, 0, -step.z);
		}
	}
	return false;
}