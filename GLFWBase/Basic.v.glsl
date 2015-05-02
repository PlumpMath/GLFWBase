#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform vec2 offset;
uniform mat4 transform;

out vec2 TexCoord;

void main(void) {
    gl_Position = transform * vec4(position.x + offset.x, position.y + offset.y, position.z, 1.0);
    TexCoord = texCoord;
}
