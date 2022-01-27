#pragma once

#include <vector>

class Mesh {
    public:
        unsigned int* m_Vbo = nullptr;
        unsigned int* m_Vao = nullptr;

        std::vector<float> m_Verticies;
        std::vector<float> m_Uvs;

        Mesh();

        void buildMesh();
};