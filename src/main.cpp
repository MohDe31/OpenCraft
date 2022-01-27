#include <application.h>
#include <perlin.h>
#include <noise.h>
#include <vector>
#include <iostream>

int main(int, char**)
{
    Perlin::Init();
    
    Application::Init();
    Application::Run();
}
