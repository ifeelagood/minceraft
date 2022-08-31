#ifndef SHADER_H
#define SHADER_H

#include "common.h"

class Shader
{
private:
    char * vertCompileLog;
    char * fragCompileLog;
    char * programLinkLog;

    GLint vertCompileStatus;
    GLint fragCompileStatus;
    GLint programLinkStatus;

public:
    GLuint ID;
    Shader(const char * vertPath, const char * fragPath);
    ~Shader();

    void use();

    void setUniformMat4(const char * uniform, glm::mat4& matrix);
};

#endif // SHADER_H