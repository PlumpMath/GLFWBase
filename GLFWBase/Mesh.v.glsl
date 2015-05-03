#version 330 core

layout (location = 0) in vec3 v_position;

uniform mat4 transform;

void main(void) {
    gl_Position = transform * vec4(v_position.x, v_position.y, v_position.z, 1.0);
}
