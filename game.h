#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern bool show_help;
extern bool show_minimap;
extern bool running;
extern int brightness;

void game_init();
void game_update();
void game_render(SDL_Renderer* renderer, TTF_Font* font);
void game_cleanup();
bool game_is_running();
void game_handle_event(SDL_Event* event);                 //játékesemények kezelése

extern int brightness;   //mert ennek globális változónak kell lennie

#endif // GAME_H
