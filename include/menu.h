#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

// Előre deklaráció
struct GameState; 

typedef enum {
    MENU_ITEM_PLAY,
    MENU_ITEM_HELP,
    MENU_ITEM_EXIT
} MenuItem;

typedef struct {
    MenuItem selected_item;
    // További menüvel kapcsolatos adatok, pl. textúrák, pozíciók
} Menu;

void menu_init(Menu* menu);
void menu_move_up(Menu* menu);
void menu_move_down(Menu* menu);
void menu_select(Menu* menu, struct GameState* game_state); // Fontos, hogy a GameState-et paraméterül kapja

// A render_menu függvényt is deklarálni kell majd, ha van
// void render_menu(SDL_Renderer* renderer, const Menu* menu);

#endif // MENU_H