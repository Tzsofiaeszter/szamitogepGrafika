#ifndef INIT_H
#define INIT_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <GL/gl.h> 

extern SDL_Window* window;
extern SDL_GLContext gl_context;

// Fényforrás struktúra
typedef struct {
    GLenum id;          // Fényforrás azonosítója (GL_LIGHT0, GL_LIGHT1, stb.)
    GLfloat position[4]; // Fény pozíciója (x, y, z, 1.0f a pontszerű fényhez)
    GLfloat ambient[4];    // Környezeti fényerősség (r, g, b, a)
    GLfloat diffuse[4];    // Diffúz fényerősség (r, g, b, a)
    GLfloat specular[4];   // Spekuláris fényerősség (r, g, b, a)
} Light;

extern SDL_Window* window;
extern SDL_GLContext gl_context;

bool init_sdl();
int init();                      // OpenGL inicializálás
void init_light(Light* light); // Fényforrás inicializálása OpenGL-ben
void cleanup();

#endif