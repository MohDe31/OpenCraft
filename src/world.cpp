#include <world.h>
#include <chunk.h>
#include <noise.h>

World::World()
{
    for(int i = 0; i < 3; i+=1)
    for(int j = 0; j < 3; j+=1)
        chunks[i][j] = Chunk(i, j, GenerateHeightMap(CHUNK_WIDTH, CHUNK_LENGTH, CHUNK_HEIGHT, 0.04, i * CHUNK_WIDTH, j * CHUNK_LENGTH));
}