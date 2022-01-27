#pragma once

#include <math.h>
#include <random>
#include <time.h>

#define _Pi 3.141592653589793
#define scaled_cosine(i) 0.5 * (1.0 - cos(i * _Pi))

const int PERLIN_YWRAPB = 4;
const int PERLIN_YWRAP = 1 << PERLIN_YWRAPB;
const int PERLIN_ZWRAPB = 8;
const int PERLIN_ZWRAP = 1 << PERLIN_ZWRAPB;
const int PERLIN_SIZE = 4095;

const int perlin_octaves = 4;
const float perlin_amp_falloff = 0.5F;

class Perlin{
    public:
        static int seed;
        static float perlin[PERLIN_SIZE];
        
        static void Init (int seed = time(NULL));
        static float noise(float x, float y, float z);
        static float noise2D(float x, float y);

        static void setSeed(int seed);
        static int getSeed();
};
