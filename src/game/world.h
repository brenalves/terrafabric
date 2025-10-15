#pragma once

#include <stdexcept>
#include <unordered_map>
#include <glm/glm.hpp>

#include "chunk.h"

#define WORLD_SIZE 2

struct Vec3Hash
{
    std::size_t operator()(const glm::ivec3& v) const
    {
        return ((std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1)) >> 1) ^ (std::hash<int>()(v.z) << 1);
    }
};

class World
{
public:
    World();
    ~World();

    void generateInitialChunks();
    void update();

    Block getBlockAt(glm::vec3 position);
    Chunk* getChunkAt(glm::vec3 position);

    inline std::unordered_map<glm::ivec3, Chunk*, Vec3Hash>& getChunks() { return _chunks; }

    inline static World* getInstance() { return _instance; }

private:
    std::unordered_map<glm::ivec3, Chunk*, Vec3Hash> _chunks;

    static World* _instance;
};