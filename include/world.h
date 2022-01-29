#pragma once

#include <chunk.h>

#include <map>

class World {
    public:
        std::map<std::pair<int, int>, Chunk> chunkStore;
        World();


        void update();
};