#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

#include "menu.h" // Menu*
#include "game_state.h" // GameState*

struct App; 

// Közös háttér kirajzolás fényerő figyelembevételével
void render_common_background(SDL_Renderer* renderer, int width, int height, int brightness);

// Menü kirajzolása
void render_menu(SDL_Renderer* renderer, const Menu* menu, const GameState* game_state, const struct App* app);

// Súgó képernyő kirajzolása
void render_help(SDL_Renderer* renderer, const GameState* game_state, const struct App* app);

// Függvény a textúra előnézet megjelenítéséhez (ha máshol van, pl. camera.c)
// void show_texture_preview(void);

#endif 