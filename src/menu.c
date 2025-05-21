#include "menu.h"
#include "game_state.h"

#include <string.h>
#include <SDL2/SDL.h>

/*
Inicializálja a Menü struktúrát alapértelmezett értékekkel.
Beállítja az induló állapotot, az elérhető menüpontokat, azok számát és megjelenítési jellemzőit.
*/
    void menu_init(Menu* menu) {
        menu->state = MENU_MAIN;
        menu->selected_item = 0;
        menu->items[0] = "Játék indítása";
        menu->items[1] = "Kilépés";
        menu->item_count = 2;       // Menü opciók száma
        menu->item_height = 40;     // Menüelemek közötti magasság
        menu->item_margin = 10;     // Különbség az elemek között
    }

/*
Feldolgozza a billentyűleütéseket a menüben való navigáláshoz.
A fel/le gombokkal mozgatja a kijelölést, Enterrel kiválasztja a pontot.
*/
    void menu_handle_input(Menu* menu, SDL_Event* event, int* running, bool* start_game) {
        if (event->type == SDL_KEYDOWN) {
            switch (event->key.keysym.sym) {
                case SDLK_UP:
                    menu->selected_item = (menu->selected_item - 1 + menu->item_count) % menu->item_count;
                    break;
                case SDLK_DOWN:
                    menu->selected_item = (menu->selected_item + 1) % menu->item_count;
                    break;
                case SDLK_RETURN:
                    if (menu->selected_item == 0) {
                        *start_game = true;
                    } else if (menu->selected_item == 1) {
                        *running = 0;
                    }
                    break;
            }
        }
    }

//Egyet lép vissza a menüpontok között (nem forgó).
    void menu_move_up(Menu* menu) {
        if (menu->selected_item > 0) {
            menu->selected_item--;
        }
    }

//Egyet lép előre a menüpontok között (nem forgó).
    void menu_move_down(Menu* menu) {
        if (menu->selected_item < menu->item_count - 1) {
            menu->selected_item++;
        }
    }

/*
A kiválasztott menüpont szövegének megfelelően módosítja a játék állapotát.
pl. elindítja a játékot, megjeleníti a súgót, kilép, stb.
*/
    void menu_select(Menu* menu, GameState* state) {
        if (menu->items != NULL && menu->selected_item >= 0 && menu->selected_item < menu->item_count) {
            const char* selected_text = menu->items[menu->selected_item];
            if (strcmp(selected_text, "Start Game") == 0) {
                state->current_scene = SCENE_GAME;
            } else if (strcmp(selected_text, "Help") == 0) {
                state->current_scene = SCENE_HELP;
            } else if (strcmp(selected_text, "Exit") == 0) {
                state->running = false;
            }
            // Ide jöhetnek további menüpontok kezelése
            else if (strcmp(selected_text, "Options") == 0) {
                state->current_scene = SCENE_OPTIONS; 
                state->is_options_menu_active = true;
                state->show_menu = false; 
            }
            // És így tovább a többi menüponttal...
        }
    }