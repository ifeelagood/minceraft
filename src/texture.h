#ifndef TEXTURE_H
#define TEXTURE_H

#include "common.h"

static unsigned int textureUnitIndex = 0;

class Texture
{
private:
    int width, height, bpp;

public:
    GLuint ID;
    GLuint unit;

    Texture(const char * path);
    ~Texture();

    void bind();
    void unbind();
};

#endif // TEXTURE_H