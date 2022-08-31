#ifndef VBO_H
#define VBO_H

#include "common.h"
#include <glm/fwd.hpp>

class VBO
{
public:
    GLuint ID;
    VBO();
    ~VBO();

    void bind();
    void unbind();

    void setData(GLsizeiptr size, const void * data);
};

#endif // VBO_H