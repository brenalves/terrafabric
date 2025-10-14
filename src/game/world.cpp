#include "world.h"

World* World::_instance = nullptr;

World::World()
{
    if(_instance)
    {
        throw std::runtime_error("World instance already exists!");
    }

    _instance = this;

    _chunk = new Chunk(glm::vec3(0.0f, 0.0f, -CHUNK_SIZE_Z));
    _chunk->generateMesh();
}

World::~World()
{
    delete _chunk;

    _instance = nullptr;
}

void World::update()
{
}
