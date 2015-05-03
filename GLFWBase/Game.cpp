#include "Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ResourcePath.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

Game::Game(GLFWwindow *window) {
    this->window = window;
}

void Game::run() {
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint program = createShaderProgram(getResourcePath("Mesh.v", "glsl").c_str(),
                                         getResourcePath("Mesh.f", "glsl").c_str());
    
    static const GLfloat verts[] = {
        0.5f,   0.5f, 0.0f,
        0.5f,  -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };
    
    GLuint uniform_transform = glGetUniformLocation(program, "transform");
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    
    glClearColor(0.98, 0.98, 0.98, 1.0);
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        
        glVertexAttribPointer(0,                 // attribute nr
                              3,                 // number of elements per vertex
                              GL_FLOAT,          // the type of each element
                              GL_FALSE,          // take our values as-is
                              3 * sizeof(float), // size of all attributes
                              0);                // offset
        glEnableVertexAttribArray(0);
        
        glm::mat4 transform = glm::rotate(glm::mat4(), (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniform_transform, 1, GL_FALSE, glm::value_ptr(transform));
        
        glDrawArrays(GL_TRIANGLES, 0, 20);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteProgram(program);
}