#pragma once

#include <perlin.h>
#include <vector>


inline std::vector<std::vector<int>> GenerateHeightMap(int width, int length, int height, double step, int xOffset, int yOffset)
{
    xOffset *= width  * step;
    yOffset *= height * step;
    

    std::vector<std::vector<int>> heightMap(width, std::vector<int>(length));
    for(int i = 0; i < width; i+=1)
    {
        for(int j = 0; j < length; j+=1)
        {
            heightMap[i][j] = Perlin::noise2D((i * step + xOffset), (j * step + yOffset)) * height;
        }
    }

    return heightMap;
}