#include <chunk.h>
#include <vector>



float voxelVerticies[] = {
    0.0f, 0.0f, 0.0f, // 0
    1.0f, 0.0f, 0.0f, // 1
    1.0f, 1.0f, 0.0f, // 2
    0.0f, 1.0f, 0.0f, // 3

    0.0f, 0.0f, 1.0f, // 4
    1.0f, 0.0f, 1.0f, // 5
    1.0f, 1.0f, 1.0f, // 6
    0.0f, 1.0f, 1.0f, // 7
};

float voxelUvs[] = {
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f
};

// 0 1 2 2 3 0
unsigned int voxelIndices[6][4] = {
    {0, 1, 2, 3}, // BACK FACE
    {4, 5, 6, 7}, // FRONT FACE
    {7, 3, 0, 4}, // LEFT FACE
    {6, 2, 1, 5}, // RIGHT FACE
    {0, 1, 5, 4}, // BOTTOM FACE
    {3, 2, 6, 7}, // TOP FACE
};


Chunk::Chunk(int x, int y): position(glm::vec2(x, y))
{
    for (int i = 0; i < CHUNK_WIDTH; i += 1)
        for (int j = 0; j < CHUNK_LENGTH; j += 1)
            for (int k = 0; k < CHUNK_HEIGHT; k += 1)
            {
                chunkData[i][j][k] = DIRT;
            }
}

Chunk::Chunk(int x, int y, std::vector<std::vector<int>> heightMap): position(glm::vec2(x, y))
{
    for (int i = 0; i < CHUNK_WIDTH; i += 1)
        for (int j = 0; j < CHUNK_LENGTH; j += 1)
        {
            for(int k = 0; k < CHUNK_HEIGHT; k+=1)
            {
                if(k < heightMap[i][j]) chunkData[i][j][k] = DIRT;
                else chunkData[i][j][k] = AIR;
            }

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

    unsigned int vertexIndex = 0;
    int neigh[6];
    int size;
    for(int i = 0; i < CHUNK_WIDTH ; i+=1)
    for(int j = 0; j < CHUNK_LENGTH; j+=1)
    for(int k = 0; k < CHUNK_HEIGHT; k+=1)
    {
        if(chunkData[i][j][k] == AIR) continue;
        
        size = 0;
        getNeighboor(i, j, k, neigh, &size);
        for(int z = 0; z < size; z+=1)
        {
            int dir = neigh[z];



            for(auto& idx: voxelIndices[dir])
            {
                m_Mesh.m_Verticies.push_back(voxelVerticies[idx * 3 + 0] + i);
                m_Mesh.m_Verticies.push_back(voxelVerticies[idx * 3 + 1] + k);
                m_Mesh.m_Verticies.push_back(voxelVerticies[idx * 3 + 2] + j);
            }

            m_Mesh.m_Uvs.push_back(voxelUvs[0 * 2 + 0]);
            m_Mesh.m_Uvs.push_back(voxelUvs[0 * 2 + 1]);
            m_Mesh.m_Uvs.push_back(voxelUvs[2 * 2 + 0]);
            m_Mesh.m_Uvs.push_back(voxelUvs[2 * 2 + 1]);
            m_Mesh.m_Uvs.push_back(voxelUvs[3 * 2 + 0]);
            m_Mesh.m_Uvs.push_back(voxelUvs[3 * 2 + 1]);
            m_Mesh.m_Uvs.push_back(voxelUvs[1 * 2 + 0]);
            m_Mesh.m_Uvs.push_back(voxelUvs[1 * 2 + 1]);

            m_Mesh.m_Triangles.push_back(vertexIndex + 0);
            m_Mesh.m_Triangles.push_back(vertexIndex + 1);
            m_Mesh.m_Triangles.push_back(vertexIndex + 2);
            m_Mesh.m_Triangles.push_back(vertexIndex + 2);
            m_Mesh.m_Triangles.push_back(vertexIndex + 3);
            m_Mesh.m_Triangles.push_back(vertexIndex + 0);


            vertexIndex += 4;
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