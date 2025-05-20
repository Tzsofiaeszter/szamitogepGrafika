#ifndef INIT_H
#define INIT_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <GL/gl.h> 
#include "app.h"


bool init_sdl();
int init(App* app);                      // OpenGL inicializálás
void cleanup();

#endif