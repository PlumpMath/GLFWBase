#version 330 core

layout (location = 0) in vec3 v_position;

uniform mat4 transform;
uniform vec4 unicolor;

out vec4 passed_color;

void main(void) {
    gl_Position = transform * vec4(v_position.x, v_position.y, v_position.z, 1.0);
    passed_color = unicolor;
}
