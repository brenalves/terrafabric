#include "chunk.h"

Chunk::Chunk(glm::vec3 position)
    : _position(position)
{
    _mesh = new Mesh();
    BufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(2); // texCoords
    _mesh->VAO->addVertexBuffer(*_mesh->VBO, layout);

    for (int x = 0; x < CHUNK_SIZE_X; x++)
    {
        for (int y = 0; y < CHUNK_SIZE_Y; y++)
        {
            for (int z = 0; z < CHUNK_SIZE_Z; z++)
            {
                _blocks[x][y][z] = Block(BlockType::GRASS);
            }
        }
    }
}

Chunk::~Chunk()
{
    delete _mesh;
}

void Chunk::generateMesh()
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int x = 0; x < CHUNK_SIZE_X; x++)
    {
        for (int y = 0; y < CHUNK_SIZE_Y; y++)
        {
            for (int z = 0; z < CHUNK_SIZE_Z; z++)
            {
                BlockType type = _blocks[x][y][z].type;
                if (type == BlockType::AIR)
                    continue;

                float blockX = _position.x + x;
                float blockY = _position.y + y;
                float blockZ = _position.z + z;

                bool isFaceVisible[6] = {true, true, true, true, true, true}; // +X, -X, +Y, -Y, +Z, -Z

                isFaceVisible[0] = checkFaceVisibility(x + 1, y, z); // +X
                isFaceVisible[1] = checkFaceVisibility(x - 1, y, z); // -X
                isFaceVisible[2] = checkFaceVisibility(x, y + 1, z); // +Y
                isFaceVisible[3] = checkFaceVisibility(x, y - 1, z); // -Y
                isFaceVisible[4] = checkFaceVisibility(x, y, z - 1); // -Z
                isFaceVisible[5] = checkFaceVisibility(x, y, z + 1); // +Z

                for (int i = 0; i < 6; i++)
                {
                    if (isFaceVisible[i])
                        addFaceToMesh(vertices, indices, blockX, blockY, blockZ, i, type);
                }
            }
        }
    }

    _mesh->VBO->setData(vertices.size() * sizeof(float), vertices.data());
    _mesh->EBO->setData(indices.size() * sizeof(unsigned int), indices.data());
}

bool Chunk::checkFaceVisibility(int x, int y, int z)
{
    return checkFaceVisibilityLocal(x, y, z) && checkFaceVisibilityGlobal(x, y, z);
}

bool Chunk::checkFaceVisibilityLocal(int x, int y, int z)
{
    if(x < 0 || x >= CHUNK_SIZE_X ||
       y < 0 || y >= CHUNK_SIZE_Y ||
       z < 0 || z >= CHUNK_SIZE_Z)
    {
        return true; // Face is visible if it's on the edge of the chunk
    }

    return _blocks[x][y][z].type == BlockType::AIR;
}

bool Chunk::checkFaceVisibilityGlobal(int x, int y, int z)
{
    if(x > 0 && x < CHUNK_SIZE_X &&
       y > 0 && y < CHUNK_SIZE_Y &&
       z > 0 && z < CHUNK_SIZE_Z)
    {
        return true; // Face is visible if it's within the chunk
    }

    // TODO: Check neighboring chunks for block presence
    return true;
}

void Chunk::addFaceToMesh(std::vector<float> &vertices, std::vector<unsigned int> &indices, float x, float y, float z, int face, BlockType type)
{
    glm::vec2 uv = Block::getUVCoords(type, face);
    float u = uv.x;
    float v = uv.y;
    float texSize = static_cast<float>(TEXTURE_SIZE) / static_cast<float>(TEXTURE_ATLAS_SIZE);
    float u2 = u + texSize;
    float v2 = v + texSize;

    if(face == 0) // +X
    {
        vertices.insert(vertices.end(), {
            x + 1, y,     z,     u2, v,
            x + 1, y + 1, z,     u2, v2,
            x + 1, y + 1, z + 1, u,  v2,
            x + 1, y,     z + 1, u,  v
        });
    }
    else if(face == 1) // -X
    {
        vertices.insert(vertices.end(), {
            x, y,     z + 1, u,  v,
            x, y + 1, z + 1, u,  v2,
            x, y + 1, z,     u2, v2,
            x, y,     z,     u2, v
        });
    }
    else if(face == 2) // +Y
    {
        vertices.insert(vertices.end(), {
            x,     y + 1, z,     u,  v,
            x + 1, y + 1, z,     u2, v,
            x + 1, y + 1, z + 1, u2, v2,
            x,     y + 1, z + 1, u,  v2
        });
    }
    else if(face == 3) // -Y
    {
        vertices.insert(vertices.end(), {
            x,     y, z + 1, u,  v2,
            x + 1, y, z + 1, u2, v2,
            x + 1, y, z,     u2, v,
            x,     y, z,     u,  v
        });
    }
    else if(face == 4) // -Z
    {
        vertices.insert(vertices.end(), {
            x + 1, y,     z, u, v,
            x + 1, y + 1, z, u, v2,
            x,     y + 1, z, u2, v2,
            x,     y,     z, u2, v
        });
    }
    else if(face == 5) // +Z
    {
        vertices.insert(vertices.end(), {
            x,     y,     z + 1, u, v,
            x,     y + 1, z + 1, u, v2,
            x + 1, y + 1, z + 1, u2,  v2,
            x + 1, y,     z + 1, u2,  v
        });
    }

    unsigned int startIndex = vertices.size() / 5 - 4; // Each vertex has 5 components (x, y, z, u, v)
    indices.insert(indices.end(), {startIndex, startIndex + 1, startIndex + 2,
                                   startIndex + 2, startIndex + 3, startIndex});
}
