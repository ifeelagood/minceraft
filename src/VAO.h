#ifndef VAO_H
#define VAO_H

#include "common.h"
#include "VBO.h" // for linkAttribute

class VAO
{
public:
    GLuint ID;
    VAO();
    ~VAO();

    void bind();
    void unbind();

    void linkAttribute(VBO &vbo, GLuint layout, GLint size, GLenum type, GLsizei stride, const void * offset);
};

#endif // VAO_H