#ifndef COMMON_H
#define COMMON_H

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assert.h>

#include <iostream>
#include <string.h>

#define GL_VERSION_MAJOR 4
#define GL_VERSION_MINOR 6

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define CHUNK_SIZE 2

struct Cursor
{
    float x1;
    float y1;
    float x2;
    float y2;
};

typedef bool Keys[1024];

#endif // COMMON_H

