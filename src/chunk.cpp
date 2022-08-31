#include "chunk.h"

#include "common.h"
#include "cube.h"

#include <vector>

unsigned char Chunk::get(unsigned int x, unsigned int y, unsigned int z) const
{
    // return 0 if x y or z is less than 0 or greater CHUNK_SIZE
    // as x, y and z are unsigned, 0 - 1 wraps around
    if (x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE) { return 0; }

    return blocks[x][y][z];
}


void add_face(const unsigned char * face, std::vector<unsigned char> &vertex, std::vector<unsigned char> &uv, unsigned int x, unsigned int y, unsigned int z)
{
    for (unsigned int i = 0; i < 18; i+=3)
    {
        vertex.push_back(face[i  ] + x);
        vertex.push_back(face[i+1] + y);
        vertex.push_back(face[i+2] + z);
    }

    for (int i = 0; i < 12; i++)
    {
        uv.push_back(cube_face_uv_byte[i]);
    }
}

void Chunk::update(VBO &vbo_vertex, VBO &vbo_uv)
{
    if (!this->changed) { return; }
    this->changed = false;

    std::vector<unsigned char> vertex;
    std::vector<unsigned char> uv;

    unsigned int blocks = 0;

    for (unsigned int x = 0; x < CHUNK_SIZE; x++)
    {
        for (unsigned int y = 0; y < CHUNK_SIZE; y++)
        {
            for (unsigned int z = 0; z < CHUNK_SIZE; z++)
            {
                unsigned char block = get(x, y, z);
                if (!block) { continue; }

                // right face
                if (!get(x + 1, y, z))
                {
                    add_face(cube_right_vertex_byte, vertex, uv, x, y, z);
                }
                // left face
                if (!get(x - 1, y, z))
                {
                    add_face(cube_left_vertex_byte, vertex, uv, x, y, z);
                }
                // top face
                if (!get(x, y + 1, z))
                {
                    add_face(cube_top_vertex_byte, vertex, uv, x, y, z);
                }
                // bottom face
                if (!get(x, y - 1, z))
                {
                    add_face(cube_bottom_vertex_byte, vertex, uv, x, y, z);
                }
                // front face
                if (!get(x, y, z + 1))
                {
                    add_face(cube_front_vertex_byte, vertex, uv, x, y, z);
                }
                // back face
                if (!get(x, y, z - 1))
                {
                    add_face(cube_back_vertex_byte, vertex, uv, x, y, z);
                }
            }
        }
    }

    verticies = vertex.size();

    vbo_vertex.setData(vertex.size(), &vertex[0]);
    vbo_uv.setData(uv.size(), &uv[0]);
}

