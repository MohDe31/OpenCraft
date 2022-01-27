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
    if(m_Vao == nullptr){
        m_Vao = new unsigned int;
        glGenVertexArrays(1, m_Vao);
    }

    float vertices[m_Verticies.size()];
    for(int i = 0; i < m_Verticies.size(); i+=1)
        vertices[i] = m_Verticies[i];

        
    glBindVertexArray(*m_Vao);

    
    glBindBuffer(GL_ARRAY_BUFFER, *m_Vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}