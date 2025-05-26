#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

#include "app.h"

void render_help_screen(const App* app);
void draw_background(App* app , GLuint texture);
#endif 