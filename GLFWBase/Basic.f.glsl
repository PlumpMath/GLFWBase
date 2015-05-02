#version 330 core

//in float instid;
in vec2 TexCoord;
uniform sampler2D ourTexture;
out vec4 color;

void main(void) {
    color = texture(ourTexture, TexCoord) * vec4(0.9, 0.9, 1.0, 1.0f);
    // color = vec4(1.0f, 0.5f, instid * 0.1f, 1.0f);
}
