#pragma once

#include <stdexcept>

#include "chunk.h"

class World
{
public:
    World();
    ~World();

    void update();

    inline Chunk* getChunk() const { return _chunk; }

    inline static World* getInstance() { return _instance; }

private:
    Chunk* _chunk;

    static World* _instance;
};