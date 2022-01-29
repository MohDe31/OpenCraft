#include <world.h>
#include <chunk.h>
#include <noise.h>
#include <renderer.h>
#include <application.h>

World::World() {}


const int xWorldOffset = 100;
const int zWorldOffset = 100;
const int renderSize = 4;

void World::update()
{
    // Check the player position
    // Check if the chunks are loaded
    // IF YES render them
    // ELSE generate them and render them

    int x = Application::camera.transform.position.x / CHUNK_WIDTH;
    int z = Application::camera.transform.position.z / CHUNK_LENGTH;

    for(int i = 0; i < renderSize * 2; i+=1)
    for(int j = 0; j < renderSize * 2; j+=1)
    {
        std::pair<int, int> key = {x - renderSize + i, z - renderSize + j};

        if(!chunkStore.count(key)){
            chunkStore[key] = Chunk(key.first, key.second, GenerateHeightMap(CHUNK_WIDTH, 
                                                                             CHUNK_LENGTH, 
                                                                             CHUNK_HEIGHT, 
                                                                             0.01f, 
                                                                             key.first + xWorldOffset, 
                                                                             key.second + zWorldOffset));

            chunkStore[key].generateMesh();
        }

        chunk_renderer(chunkStore[key], Application::program);
    }
}