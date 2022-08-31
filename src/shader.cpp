#include "shader.h"

#include <cstddef>
#include <stdio.h>

char * readFile(const char * path)
{
    FILE * file = fopen(path, "rt");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char * data = (char *) malloc(size + 1);
    fread(data, 1, size, file);
    data[size] = '\0';
    fclose(file);
    return data;
}

Shader::Shader(const char * vertPath, const char * fragPath)
{
    char * vertSource = readFile(vertPath);
    char * fragSource = readFile(fragPath);

    GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertID, 1, &vertSource, NULL);
    glShaderSource(fragID, 1, &fragSource, NULL);

    glCompileShader(vertID);
    glGetShaderiv(vertID, GL_COMPILE_STATUS, &vertCompileStatus);

    if (vertCompileStatus == GL_FALSE)
    {
        GLint logLength;
        glGetShaderiv(vertID, GL_INFO_LOG_LENGTH, &logLength);
        vertCompileLog = (char *) malloc(logLength);
        glGetShaderInfoLog(vertID, logLength, NULL, vertCompileLog);
        fprintf(stderr, "VERTEX SHADER COMPILATION FAILED\n%s: %s\n", vertPath, fragCompileLog);
    }

    glCompileShader(fragID);
    glGetShaderiv(fragID, GL_COMPILE_STATUS, &fragCompileStatus);
    if (fragCompileStatus == GL_FALSE)
    {
        GLint logLength;
        glGetShaderiv(fragID, GL_INFO_LOG_LENGTH, &logLength);
        fragCompileLog = (char *) malloc(logLength);
        glGetShaderInfoLog(fragID, logLength, NULL, fragCompileLog);
        fprintf(stderr, "FRAGMENT SHADER COMPILATION FAILED\n%s: %s\n", fragPath, fragCompileLog);
    }

    std::cout << "freeing shader source\n";
    // free shader source
    free(vertSource);
    free(fragSource);

    if (vertCompileStatus == GL_TRUE && fragCompileStatus == GL_TRUE)
    {
        ID = glCreateProgram();

        glAttachShader(ID, vertID);
        glAttachShader(ID, fragID);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &programLinkStatus);
        if (programLinkStatus == GL_FALSE)
        {
            GLint logLength;
            glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &logLength);
            programLinkLog = (char *) malloc(logLength);
            glGetProgramInfoLog(ID, logLength, NULL, programLinkLog);
            fprintf(stderr, "SHADER PROGRAM LINKING FAILED\n%s\n", programLinkLog);
        }
        else
        {
        std::cout << "sucessfully compiled and linked shaders\n";
        }
    }

    // free up shaders
    glDeleteShader(vertID);
    glDeleteShader(fragID);

    if (vertCompileStatus == GL_FALSE || fragCompileStatus == GL_FALSE || programLinkStatus == GL_FALSE)
    {
        std::cerr << "SHADER PROGRAM COULD NOT BE CREATED. LINKING/COMPILING FAILED\n";
        glDeleteProgram(ID);
    }
}

Shader::~Shader()
{
    glDeleteProgram(ID);

    if (vertCompileStatus == GL_FALSE)
    {
        free(vertCompileLog); 
    }
    if (fragCompileStatus == GL_FALSE)
    {
        free(fragCompileLog);
    }
    if (programLinkStatus == GL_FALSE)
    {
        free(programLinkLog);
    }
}

void Shader::use()
{
    glUseProgram(ID);    
}

void Shader::setUniformMat4(const char *uniform, glm::mat4 &matrix)
{
    GLint loc = glGetUniformLocation(ID, uniform);
    if (loc == -1)
    {
        fprintf(stderr, "Could not find uniform: %s\n", uniform);
        return;
    }

    glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}