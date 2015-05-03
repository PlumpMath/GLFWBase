#version 330 core

in vec4 passed_color;

out vec4 color;

void main(void) {
    color = passed_color;
}
