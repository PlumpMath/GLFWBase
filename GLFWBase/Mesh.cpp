#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ResourcePath.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

#include "Mesh.h"

using namespace std;

static const GLfloat quadVerts[] = {
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
    0.5f,  -0.5f, 0.0f,
    0.5f,   0.5f, 0.0f,
};

Mesh::Mesh() {
    mesh_program = createShaderProgram(getResourcePath("Mesh.v", "glsl").c_str(),
                                       getResourcePath("Mesh.f", "glsl").c_str());
   
    uniform_transform = glGetUniformLocation(mesh_program, "transform");
    uniform_color =     glGetUniformLocation(mesh_program, "unicolor");
    
    cout << "loc: " << uniform_transform << ", loc: " << uniform_color << endl;
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);

}

void Mesh::activate() {
    glUseProgram(mesh_program);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    
    glVertexAttribPointer(0,                 // attribute nr
                          3,                 // number of elements per vertex
                          GL_FLOAT,          // the type of each element
                          GL_FALSE,          // take our values as-is
                          3 * sizeof(float), // size of all attributes
                          0);                // offset
    glEnableVertexAttribArray(0);
}

void Mesh::draw(glm::vec3 position, glm::vec4 color) {
    glm::mat4 transform;
    transform = glm::translate(transform, position);
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(uniform_transform, 1, GL_FALSE, glm::value_ptr(transform));
    glUniform4fv(uniform_color, 1, glm::value_ptr(color));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 12);
}

void Mesh::deactivate() {
    glDisableVertexAttribArray(0);
}

Mesh::~Mesh() {
    glDeleteProgram(mesh_program);
}


