#ifndef LIGHT_H
#define LIGHT_H

#include <GL/gl.h>

// Fényforrás struktúra
typedef struct {
    GLenum id;          // Fényforrás azonosítója (GL_LIGHT0, GL_LIGHT1, stb.)
    GLfloat position[4]; // Fény pozíciója (x, y, z, 1.0f a pontszerű fényhez)
    GLfloat ambient[4];    // Környezeti fényerősség (r, g, b, a)
    GLfloat diffuse[4];    // Diffúz fényerősség (r, g, b, a)
    GLfloat specular[4];   // Spekuláris fényerősség (r, g, b, a)
} Light;

void init_light(Light* light); // Fényforrás inicializálása OpenGL-ben

#endif