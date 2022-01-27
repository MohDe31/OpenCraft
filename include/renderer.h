#pragma once

#include <shader.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <chunk.h>

#include <vector>
#include <iostream>
void chunk_renderer(Chunk chunk, Shader program)
{
    glBindVertexArray(*chunk.m_Mesh.m_Vao);


    // std::cout << (chunk.chunkData[0][0][0]==AIR?"AIR":"DIRT") << std::endl;

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(chunk.position.x * CHUNK_WIDTH, 0, chunk.position.y * CHUNK_LENGTH));
    program.setMat4("model", glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, chunk.m_Mesh.m_Verticies.size());
};