#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <stdexcept>

#include "components/mesh.h"
#include "block.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16

class Chunk
{
public:
    Chunk(glm::vec3 position);
    ~Chunk();

    void generateMesh();

    Block& getBlockAt(int x, int y, int z);

    inline glm::vec3 getPosition() const { return _position; }
    inline Mesh* getMesh() const { return _mesh; }

private:
    bool checkFaceVisibility(int x, int y, int z);
    bool checkFaceVisibilityLocal(int x, int y, int z);
    bool checkFaceVisibilityGlobal(int x, int y, int z);
    void addFaceToMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, float x, float y, float z, int face, BlockType type);

private:
    glm::vec3 _position;
    Block _blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z]; // 16x16x16 chunk of blocks
    Mesh* _mesh;
};