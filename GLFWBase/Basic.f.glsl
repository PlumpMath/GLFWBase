#version 330 core

in vec2 f_texCoord;
uniform sampler2D ourTexture;
out vec4 color;

void main(void) {
    color = texture(ourTexture, f_texCoord) * vec4(0.9, 0.9, 1.0, 1.0f);
}
