#ifndef INIT_H
#define INIT_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <GL/gl.h> 

struct App;

bool init_sdl();
int init(App* app);  // OpenGL inicializálás
//void cleanup();
void reshape(int width, int height);

#endif
