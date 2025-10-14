#pragma once

#define TEXTURE_ATLAS_SIZE 256
#define TEXTURE_SIZE 32

enum class BlockType
{
    AIR,
    DIRT,
    GRASS,
    STONE,
    BEDROCK
};

struct Block
{
    BlockType type;

    Block() : type(BlockType::AIR) {}
    Block(BlockType t)
        : type(t)
    {
    }

    static glm::vec2 getUVCoords(BlockType type, int face)
    {
        int tileX = 0;
        int tileY = 0;

        switch (type)
        {
        case BlockType::GRASS:
            if (face == 2) // Top
            {
                tileX = 0;
                tileY = 0;
            }
            else if (face == 3) // Bottom
            {
                tileX = 2;
                tileY = 0;
            }
            else // Sides
            {
                tileX = 1;
                tileY = 0;
            }
            break;
        case BlockType::DIRT:
            tileX = 2;
            tileY = 0;
            break;
        case BlockType::STONE:
            tileX = 3;
            tileY = 0;
            break;
        case BlockType::BEDROCK:
            tileX = 4;
            tileY = 0;
            break;
        }

        float u = (tileX * TEXTURE_SIZE) / static_cast<float>(TEXTURE_ATLAS_SIZE);
        float v = (tileY * TEXTURE_SIZE) / static_cast<float>(TEXTURE_ATLAS_SIZE);

        return glm::vec2(u, v);
    }
};