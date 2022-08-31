#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"
#include "VBO.h"

class Chunk
{
private:
    unsigned char blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

public:
    Chunk() {};
    ~Chunk() {};

    bool changed = false;
    unsigned int verticies = 0;

    unsigned char get(unsigned int x, unsigned int y, unsigned int z) const;
    void set(unsigned int x, unsigned int y, unsigned int z, unsigned char value) { this->changed = true; this->blocks[x][y][z] = value; }

    void update(VBO& vbo_vertex, VBO& vbo_uv);
};


#endif // CHUNK_H