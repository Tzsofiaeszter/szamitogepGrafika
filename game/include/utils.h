#ifndef UTILS_H
#define UTILS_H

#include <GL/gl.h>

typedef struct vec3{
    float x;
    float y;
    float z;
} vec3;

typedef struct Color{
    float red;
    float green;
    float blue;
} Color;

typedef struct Material{
    struct Color ambient;
    struct Color diffuse;
    struct Color specular;
    float shininess;

    GLuint ajto_texture;
    GLuint ajtob_texture;
    GLuint fa1_texture;
    GLuint fa2_texture;
    GLuint fa3_texture;
    GLuint fa4_texture;
    GLuint szek_texture;
    GLuint barna_texture;
    GLuint szonyeg_texture;
    GLuint kek_texture;
    GLuint fal_texture;
    GLuint cserep_texture;
    GLuint book_texture;
    GLuint csillar_texture;
    
} Material;

double degree_to_radian(double degree);

#endif 
