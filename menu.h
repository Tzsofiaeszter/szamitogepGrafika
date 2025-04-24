#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "game_state.h"

// Menü állapotok
typedef enum MenuState{
    MENU_MAIN,
    MENU_PLAY,
    MENU_QUIT
} MenuState;

// Menü állapotok
typedef struct Menu{
    int selected_index;
    int item_count;
} Menu;

// Menü inicializálása
void menu_init(Menu* menu);

// Menü eseménykezelés (pl. nyilak, Enter)
void menu_handle_input(Menu* menu, SDL_Event* event, int* running, bool* start_game);

// Menü kirajzolása
void menu_render(Menu* menu, SDL_Renderer* renderer, TTF_Font* font, int width, int height);

//mivel ez grafikai megjelenítést végez a menühöz kapcsolódóan
void render_menu(SDL_Renderer* renderer, TTF_Font* font)

#endif // MENU_H

