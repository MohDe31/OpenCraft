#include <chunk.h>
#include <iostream>

#include <vector>



float vs[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 0
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // 1
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // 2
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // 3

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // 4
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // 5
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // 6
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // 7

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // 8
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // 9
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // 10

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // 11
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // 12
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // 13

    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // 14

    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, // 15
};

unsigned int m[6][6] = {
    {0, 1, 2, 2, 3, 0     },
    {4, 5, 6, 6, 7, 4     },
    {8, 9, 10, 10, 4, 8   },
    {11, 2, 12, 12, 13, 11},
    {10, 14, 5, 5, 4, 10  },
    {3, 2, 11, 11, 15, 3  },
};

Chunk::Chunk(float x, float y): position(glm::vec2(x, y))
{
    for (int i = 0; i < CHUNK_WIDTH; i += 1)
        for (int j = 0; j < CHUNK_LENGTH; j += 1)
            for (int k = 0; k < CHUNK_HEIGHT; k += 1)
            {
                chunkData[i][j][k] = DIRT;
            }
}

Chunk::Chunk() {}

void Chunk::getNeighboor(int i, int j, int k, int* output, int* size)
{
    if (k == CHUNK_HEIGHT - 1 || chunkData[i][j][k + 1] == AIR)
    {
        *(output + (*size)++) = 5;
    }

    if (k == 0 || chunkData[i][j][k - 1] == AIR)
    {
        *(output + (*size)++) = 4;
    }

    if (i == CHUNK_WIDTH - 1 || chunkData[i + 1][j][k] == AIR)
    {
        *(output + (*size)++) = 3;
    }

    if (i == 0 || chunkData[i - 1][j][k] == AIR)
    {
        *(output + (*size)++) = 2;
    }

    if (j == CHUNK_LENGTH - 1 || chunkData[i][j + 1][k] == AIR)
    {
        *(output + (*size)++) = 1;
    }

    if (j == 0 || chunkData[i][j - 1][k] == AIR)
    {
        *(output + (*size)++) = 0;
    }
    
}

void Chunk::calculateVerticies()
{
    m_Mesh.m_Verticies.clear();

    int neigh[6];
    int size;
    for(int i = 0; i < CHUNK_WIDTH ; i+=1)
    for(int j = 0; j < CHUNK_LENGTH; j+=1)
    for(int k = 0; k < CHUNK_HEIGHT; k+=1)
    {
        size = 0;
        getNeighboor(i, j, k, neigh, &size);
        for(int z = 0; z < size; z+=1)
        {
            int dir = neigh[z];

            for(auto& idx: m[dir])
            {
                m_Mesh.m_Verticies.push_back(vs[idx * 5 + 0] + i);
                m_Mesh.m_Verticies.push_back(vs[idx * 5 + 1] + k);
                m_Mesh.m_Verticies.push_back(vs[idx * 5 + 2] + j);
                m_Mesh.m_Verticies.push_back(vs[idx * 5 + 3]);
                m_Mesh.m_Verticies.push_back(vs[idx * 5 + 4]);
            }
        }
    }
}

void Chunk::generateMesh()
{
    if(!m_Mesh.m_Verticies.size())
    {
        calculateVerticies();
    }
    m_Mesh.buildMesh();
}