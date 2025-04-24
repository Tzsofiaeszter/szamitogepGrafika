#ifndef ELOSZOBA_H
#define ELOSZOBA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct Eloszoba{
    bool puzzle_solved;
    bool door_unlocked;
} Eloszoba;

// Inicializálás
void eloszoba_init(Eloszoba* szoba);

// Eseménykezelés (pl. kód beírása)
void eloszoba_handle_event(SDL_Event* event, Eloszoba* szoba, char* input_buffer, int* input_length);

// Kirajzolás
void eloszoba_render(SDL_Renderer* renderer, TTF_Font* font, Eloszoba* szoba, const char* input_buffer);

#endif
