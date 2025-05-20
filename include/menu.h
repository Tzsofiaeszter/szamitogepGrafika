#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include"game_state.h"
#include <stdbool.h>

typedef enum {
    MENU_MAIN,
    MENU_HELP,
    MENU_EXIT,
} MenuState;

typedef struct {
    MenuState state;
    int selected_item;
    const char* items[3];
    int item_count;
    int item_height;
    int item_margin;
} Menu;

void menu_move_up(Menu* menu);
void menu_move_down(Menu* menu);
void menu_select(Menu* menu, GameState* state);


void menu_init(Menu* menu);
void menu_handle_input(Menu* menu, SDL_Event* event, int* running, bool* start_game);

#endif 