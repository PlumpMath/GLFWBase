
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ResourcePath.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

using namespace std;

int main(void)
{
    GLFWwindow* window;
    
    if (!glfwInit()) {
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    window = glfwCreateWindow(640, 480, "Wie geht's?", NULL, NULL);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // MUST SETUP GLEW BEFORE CALLING OPEN GL FUNCTIONS!!!
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        printf("Failed to initialize GLEW\n");
        return -1;
    }
   
    GLuint program = CreateShaderProgram(getResourcePath("Basic.v", "glsl").c_str(),
                                         getResourcePath("Basic.f", "glsl").c_str());
  
    static const GLfloat triangle_vertices[] = {
        0.5f,   0.5f, 0.0f,   1.0f, 0.0f,
        0.5f,  -0.5f, 0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f,
        
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f,
        0.5f,   0.5f, 0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f
    };
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    
    GLuint texture1 = LoadTexture("jelly");
    GLuint texture2 = LoadTexture("blah");
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    glClearColor(0.98, 0.98, 0.98, 1.0);
    
    GLuint uniform_offset = glGetUniformLocation(program, "offset");
        
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        
        glVertexAttribPointer(0,                 // attribute nr
                              3,                 // number of elements per vertex, here (x,y)
                              GL_FLOAT,          // the type of each element
                              GL_FALSE,          // take our values as-is
                              5 * sizeof(float), // size of all attributes
                              0);                // offset
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              5 * sizeof(float),
                              (const void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        glUniform2f(uniform_offset, -0.2f, -0.2f);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glDrawArrays(GL_TRIANGLES, 0, 20);
        
        glUniform2f(uniform_offset, 0.3f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glDrawArrays(GL_TRIANGLES, 0, 20);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}