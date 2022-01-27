#include <world.h>
#include <chunk.h>





World::World()
{
    for(int i = 0; i < 3; i+=1)
    for(int j = 0; j < 3; j+=1)
        chunks[i][j] = Chunk(i, j);
}