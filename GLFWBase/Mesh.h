#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class Mesh {
    GLuint mesh_program;
    GLuint uniform_transform;
    GLuint uniform_color;
    GLuint vbo;
public:
    Mesh();
    ~Mesh();
    void activate();
    void deactivate();
    void draw(glm::vec3 position, glm::vec4 color);
};

