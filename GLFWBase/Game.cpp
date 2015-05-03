#include "Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ResourcePath.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"
#include "Mesh.h"

Game::Game(GLFWwindow *window) {
    this->window = window;
}

void Game::run() {
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glClearColor(0.98, 0.98, 0.98, 1.0);
    
    Mesh m1;
    m1.activate();
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        m1.draw(glm::vec3(-0.2,  0.0, 0.0), glm::vec4(0.2, 0.7, 0.9, 1.0));
        m1.draw(glm::vec3( 0.3, -0.1, 0.0), glm::vec4(0.9, 0.3, 0.5, 1.0));
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}