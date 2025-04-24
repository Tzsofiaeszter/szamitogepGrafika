// Ezek a fájlok felelősek az aktuális szoba kinézetének (leírásának) megjelenítéséért.

#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

// Szöveg megjelenítése adott pozícióban
void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);

// Súgó overlay megjelenítése
void render_help_overlay(SDL_Renderer* renderer, TTF_Font* font, int window_width, int window_height, bool show);

#endif
