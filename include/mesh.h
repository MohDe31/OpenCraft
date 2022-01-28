#pragma once

#include <vector>

class Mesh {
    public:
        unsigned int* m_Vbo = nullptr;
        unsigned int* m_Vao = nullptr;
        unsigned int* m_Ebo = nullptr;

        std::vector<unsigned int> m_Triangles;
        std::vector<float> m_Verticies;
        std::vector<float> m_Uvs;

        Mesh();

        void buildMesh();
};