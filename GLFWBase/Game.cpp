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

float fov = 45.0f;

static void cursorMoved(GLFWwindow* window, double xpos, double ypos) {
    fov = (xpos / 640.0f) * 3.14f;
}

void Game::run() {
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.98, 0.98, 0.98, 1.0);
    
    Mesh m1;
    m1.activate();
    
    glfwSetCursorPosCallback(window, cursorMoved);
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        glm::mat4 cam = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f),
                                    glm::vec3(0.0f, 0.0f, 0.0f),
                                    glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 proj = glm::perspective(fov, (float)640/(float)480, 0.1f, 100.0f);
        glm::mat4 view = proj * cam;
        
        m1.draw(glm::vec3(-1.0, 0.0, 0.0), glm::vec4(0.2, 0.5, 0.9, 1.0), view);
        m1.draw(glm::vec3( 0.0, 0.0, 0.0), glm::vec4(0.9, 0.8, 0.1, 1.0), view);
        m1.draw(glm::vec3( 1.0, 0.0, 0.0), glm::vec4(0.9, 0.3, 0.5, 1.0), view);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}