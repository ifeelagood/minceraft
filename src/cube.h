#ifndef CUBE_H
#define CUBE_H



static const unsigned char cube_face_uv_byte[] = {
    0, 0,
    1, 0,
    1, 1,
    0, 0,
    1, 1,
    0, 1,
};

static const unsigned char cube_front_vertex_byte[] = {
    0, 0, 1, 
    1, 0, 1, 
    1, 1, 1, 
    0, 0, 1, 
    1, 1, 1, 
    0, 1, 1, 
};

static const unsigned char cube_back_vertex_byte[] = {
    1, 0, 0,
    0, 0, 0, 
    0, 1, 0,
    1, 0, 0, 
    0, 1, 0,
    1, 1, 0,
};

static const unsigned char cube_left_vertex_byte[] = {
    0, 0, 0,
    0, 0, 1, 
    0, 1, 1, 
    0, 0, 0, 
    0, 1, 1, 
    0, 1, 0, 
};

static const unsigned char cube_right_vertex_byte[] = {
    1, 0, 1, 
    1, 0, 0, 
    1, 1, 0, 
    1, 0, 1, 
    1, 1, 0,
    1, 1, 1,
};

static const unsigned char cube_top_vertex_byte[] = {
    0, 1, 1,
    1, 1, 1, 
    1, 1, 0, 
    0, 1, 1,
    1, 1, 0, 
    0, 1, 0,
};


static const unsigned char cube_bottom_vertex_byte[] = {
    0, 0, 0,
    1, 0, 0, 
    1, 0, 1, 
    0, 0, 0, 
    1, 0, 1,
    0, 0, 1,
};

#endif // CUBE_H