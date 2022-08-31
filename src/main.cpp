#include "common.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <random>

#include "camera.h"
#include "VBO.h"
#include "VAO.h"
#include "shader.h"
#include "texture.h"
#include "chunk.h"
#include "cube.h"

static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
static void mouse_callback(GLFWwindow * window, double xpos, double ypos);
static void error_callback(int error, const char* description);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static void init_glfw();
static void init_glad();

struct Timer
{ 
    float t1;
    float t2;
    float deltaTime;
} timer;


void tick()
{
    timer.t2 = glfwGetTime();
    timer.deltaTime = timer.t2 - timer.t1;
    timer.t1 = timer.t2;
}

Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);
Cursor cursor;
Keys keys;

int main()
{
    GLFWwindow * window;
    init_glfw();

    window = glfwCreateWindow(1920, 1080, "Minceraft", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    init_glad();

    Shader shader("res/shaders/vert.glsl", "res/shaders/frag.glsl");
    VAO vao;
    
    vao.bind();
    VBO vbo_vertex;
    vbo_vertex.bind();
    vao.linkAttribute(vbo_vertex, 0, 3, GL_BYTE, 3 * sizeof(unsigned char), (void *) 0);
    
    vbo_vertex.unbind();

    VBO vbo_uv;
    vbo_uv.bind();
    vao.linkAttribute(vbo_uv, 1, 2, GL_BYTE, 2 * sizeof(unsigned char), (void *) 0);
    
    vbo_uv.unbind();
    
    vao.unbind();
    
    // vbo_vertex.setData(sizeof(cube_front_vertex_byte), cube_front_vertex_byte);
    // vbo_uv.setData(sizeof(cube_face_uv_byte), cube_face_uv_byte);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    camera.setDimensions(width, height);
    camera.setPosition(glm::vec3(1.0f, 1.0f, -1.0f));

    Texture tex("res/textures/cobblestone.jpg");
    Chunk chunk;

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if (rand() % 2 == 0) { chunk.set(x, y, z, 1); }
            }
        }
    }

    chunk.update(vbo_vertex, vbo_uv);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);  
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    // glCullFace(GL_FRONT);
    // glFrontFace(GL_CCW);
    shader.use();


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);        
        tex.bind();    

        glm::mat4 mvp = camera.getMVP(glm::vec3(0, 0, 0));
        shader.setUniformMat4("mvp", mvp);
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, chunk.verticies);

        glfwSwapBuffers(window);
        glfwPollEvents();

        tick();
        camera.processKeyboard(keys, timer.deltaTime);
    }

    glfwTerminate();
}


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW ERROR: %s\n", description);
}

static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(window, true);
        }

        if (key >= 0 && key < 1024)
        {
            keys[key] = true;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        if (key >= 0 && key < 1024)
        {
            keys[key] = false;
        }
    }
}

static void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
    // update cursor struct
    cursor.x1 = cursor.x2;
    cursor.y1 = cursor.y2;
    cursor.x2 = xpos;
    cursor.y2 = ypos;

    camera.processMouseMovement(cursor);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    camera.setDimensions(width, height);
}


static void init_glfw()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);
}

static void init_glad()
{
    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Failed to load OpenGL\n";
        fprintf(stderr, "OpenGL Version: %i.%i\n", GL_VERSION_MAJOR, GL_VERSION_MINOR);

        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "OpenGL Loaded\n");
    fprintf(stdout, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    fprintf(stdout, "OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    fprintf(stdout, "OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
}
