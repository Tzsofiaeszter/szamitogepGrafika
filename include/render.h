#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// Kameraállapot
typedef struct {
    int x, y;      // Kamera pozíció
    float zoom;    // Zoom faktor
} Camera;

extern Camera camera;
extern int brightness; // Fényerő globálisan elérhető

void render_common_background(SDL_Renderer* renderer, int width, int height);

#endif
