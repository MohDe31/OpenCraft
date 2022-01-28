#include <mesh.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <iostream>


Mesh::Mesh() {}


void Mesh::buildMesh() {
    if(m_Vbo == nullptr){
        m_Vbo = new unsigned int;
        glGenBuffers(1, m_Vbo);
    }

    if(m_Ebo == nullptr){
        m_Ebo = new unsigned int;
        glGenBuffers(1, m_Ebo);
    }

    if(m_Vao == nullptr){
        m_Vao = new unsigned int;
        glGenVertexArrays(1, m_Vao);
    }

    int i = 0;

    float vertices[m_Verticies.size() + m_Uvs.size()];
    for(i = 0; i < m_Verticies.size() / 3; i+=1)
    {
        vertices[i * 5 + 0] = m_Verticies[i * 3 + 0];
        vertices[i * 5 + 1] = m_Verticies[i * 3 + 1];
        vertices[i * 5 + 2] = m_Verticies[i * 3 + 2];
        vertices[i * 5 + 3] = m_Uvs[i * 2 + 0];
        vertices[i * 5 + 4] = m_Uvs[i * 2 + 1];
    }

    unsigned int indices[m_Triangles.size()];
    for(i = 0; i < m_Triangles.size(); i+=1)
        indices[i] = m_Triangles[i];
    
    glBindVertexArray(*m_Vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, *m_Vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}