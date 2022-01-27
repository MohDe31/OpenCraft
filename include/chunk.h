#pragma once

#include <mesh.h>

#include <glm/glm/glm.hpp>

#include <vector>

enum BLOCK_TYPE {
    DIRT,
    AIR
};

enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

const int CHUNK_WIDTH  = 16;
const int CHUNK_LENGTH = 16;
const int CHUNK_HEIGHT = 256;

typedef struct Chunk {
    glm::vec2 position;
    BLOCK_TYPE chunkData[CHUNK_WIDTH][CHUNK_LENGTH][CHUNK_HEIGHT];
    
    Mesh m_Mesh;

    Chunk();
    Chunk(float x, float y);


    void getNeighboor(int i, int j, int k, int* output, int* size);
    void calculateVerticies();
    void generateMesh();
} Chunk;