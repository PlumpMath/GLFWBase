#include "TextureLoader.h"
#include "ResourcePath.h"
#include "SOIL.h"

using namespace std;

GLuint LoadTexture(string name) {
    int width, height;
    string path = getResourcePath(name, "jpg");
    unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    if(!image) cout << "Failed to load image." << endl;
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    return texture;
}
