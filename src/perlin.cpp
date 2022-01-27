#include <perlin.h>

#include <math.h>
#include <random>
#include <time.h>

int Perlin::seed;
float Perlin::perlin[PERLIN_SIZE];

void Perlin::Init(int seed)
{
    Perlin::seed = seed;
    srand(Perlin::seed);

    for (int i = 0; i < PERLIN_SIZE; ++i)
    {
        Perlin::perlin[i] = (float)rand() / RAND_MAX;
    }
}

float Perlin::noise(float x, float y, float z)
{
    if (x < 0)
    {
        x = -x;
    }

    if (y < 0)
    {
        y = -y;
    }

    if (z < 0)
    {
        z = -z;
    }

    int xi = floor(x);
    int yi = floor(y);
    int zi = floor(z);

    float xf = x - xi;
    float yf = y - yi;
    float zf = z - zi;

    float rxf = 0;
    float ryf = 0;

    float r = 0;
    float ampl = 0.5;

    float n1 = 0;
    float n2 = 0;
    float n3 = 0;

    for (int i = 0; i < perlin_octaves; ++i)
    {
        int of = xi + (yi << PERLIN_YWRAPB) + (zi << PERLIN_ZWRAPB);

        rxf = scaled_cosine(xf);
        ryf = scaled_cosine(yf);

        n1 = Perlin::perlin[of & PERLIN_SIZE];
        n1 += rxf * (Perlin::perlin[(of + 1) & PERLIN_SIZE] - n1);
        n2 = Perlin::perlin[(of + PERLIN_YWRAP) & PERLIN_SIZE];
        n2 += rxf * (Perlin::perlin[(of + PERLIN_YWRAP + 1) & PERLIN_SIZE] - n2);
        n1 += ryf * (n2 - n1);

        of += PERLIN_ZWRAP;
        n2 = Perlin::perlin[of & PERLIN_SIZE];
        n2 += rxf * (Perlin::perlin[(of + 1) & PERLIN_SIZE] - n2);
        n3 = Perlin::perlin[(of + PERLIN_YWRAP) & PERLIN_SIZE];
        n3 += rxf * (Perlin::perlin[(of + PERLIN_YWRAP + 1) & PERLIN_SIZE] - n3);
        n2 += ryf * (n3 - n2);

        n1 += scaled_cosine(zf) * (n2 - n1);

        r += n1 * ampl;
        ampl *= perlin_amp_falloff;
        xi <<= 1;
        xf *= 2;
        yi <<= 1;
        yf *= 2;
        zi <<= 1;
        zf *= 2;

        if (xf >= 1.0)
        {
            xi += 1;
            xf -= 1;
        }

        if (yf >= 1.0)
        {
            yi += 1;
            yf -= 1;
        }

        if (zf >= 1.0)
        {
            zi += 1;
            zf -= 1;
        }
    }

    return r;
}

float Perlin::noise2D(float x, float y)
{
    return Perlin::noise(x, y, 0);
}

void Perlin::setSeed(int seed)
{
    Perlin::seed = seed;
}

int Perlin::getSeed()
{
    return Perlin::seed;
}
