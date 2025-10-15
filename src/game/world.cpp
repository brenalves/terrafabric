#include "world.h"

World* World::_instance = nullptr;

World::World()
{
    if(_instance)
    {
        throw std::runtime_error("World instance already exists!");
    }

    _instance = this;
}

World::~World()
{
    for(auto& pair : _chunks)
    {
        delete pair.second;
    }
    _chunks.clear();

    _instance = nullptr;
}

void World::generateInitialChunks()
{
    // for(int x = -WORLD_SIZE; x <= WORLD_SIZE; ++x)
    // {
    //     for(int z = -WORLD_SIZE; z <= WORLD_SIZE; ++z)
    //     {
    //         glm::ivec3 chunkPos(x * CHUNK_SIZE_X, 0, z * CHUNK_SIZE_Z);
    //         Chunk* chunk = new Chunk(glm::vec3(chunkPos));
    //         chunk->generateMesh();
    //         _chunks[chunkPos] = chunk;
    //     }
    // }

    Chunk* chunk1 = new Chunk(glm::vec3(0, 0, 0));
    chunk1->generateMesh();
    _chunks[glm::ivec3(0, 0, 0)] = chunk1;

    Chunk* chunk2 = new Chunk(glm::vec3(CHUNK_SIZE_X, 0, 0));
    chunk2->generateMesh();
    _chunks[glm::ivec3(CHUNK_SIZE_X, 0, 0)] = chunk2;

    
}

void World::update()
{
}

Chunk *World::getChunkAt(glm::vec3 position)
{
    glm::ivec3 chunkPos;
    chunkPos.x = static_cast<int>(floor(position.x / CHUNK_SIZE_X)) * CHUNK_SIZE_X;
    chunkPos.y = static_cast<int>(floor(position.y / CHUNK_SIZE_Y)) * CHUNK_SIZE_Y;
    chunkPos.z = static_cast<int>(floor(position.z / CHUNK_SIZE_Z)) * CHUNK_SIZE_Z;

    auto it = _chunks.find(chunkPos);
    if(it != _chunks.end())
    {
        return it->second;
    }
    return nullptr;
}

Block World::getBlockAt(glm::vec3 position)
{
    glm::ivec3 blockPos = glm::floor(position);
    glm::ivec3 chunkPos;
    chunkPos.x = static_cast<int>(floor(blockPos.x / CHUNK_SIZE_X)) * CHUNK_SIZE_X;
    chunkPos.y = static_cast<int>(floor(blockPos.y / CHUNK_SIZE_Y)) * CHUNK_SIZE_Y;
    chunkPos.z = static_cast<int>(floor(blockPos.z / CHUNK_SIZE_Z)) * CHUNK_SIZE_Z;

    auto it = _chunks.find(chunkPos);
    if(it != _chunks.end())
    {
        Chunk* chunk = it->second;
        int localX = blockPos.x - chunkPos.x;
        int localY = blockPos.y - chunkPos.y;
        int localZ = blockPos.z - chunkPos.z;

        return chunk->getBlockAt(localX, localY, localZ);
    }
    return Block(BlockType::AIR);
}
