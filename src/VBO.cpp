#include "VBO.h"

VBO::VBO()
{
    glGenBuffers(1, &ID);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &ID);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::setData(GLsizeiptr size, const void * data)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    unbind();
}