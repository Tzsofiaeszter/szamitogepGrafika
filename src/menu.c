#include <string.h>
#include "menu.h"
#include "game_state.h"
#include <SDL2/SDL.h>


void menu_init(Menu* menu) {
    menu->state = MENU_MAIN;
    menu->selected_item = 0;
    menu->items[0] = "Játék indítása";
    menu->items[1] = "Kilépés";
    menu->item_count = 2;       // Menü opciók száma
    menu->item_height = 40;     // Menüelemek közötti magasság
    menu->item_margin = 10;     // Különbség az elemek között
}

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

void menu_move_up(Menu* menu) {
    if (menu->selected_item > 0) {
        menu->selected_item--;
    }
}

void menu_move_down(Menu* menu) {
    if (menu->selected_item < menu->item_count - 1) {
        menu->selected_item++;
    }
}

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
            state->current_scene = SCENE_OPTIONS; // Feltételezve, hogy van egy SCENE_OPTIONS állapotod
            // Itt további logika is jöhet a beállítások menü megnyitásához

            // Példák a további logikára:

            // 1. Egy flag beállítása, ami jelzi, hogy a beállítások menü aktív
            state->is_options_menu_active = true;

            // 2. A beállítások menü adatainak inicializálása (ha szükséges)
            // if (state->options_menu == NULL) {
            //     state->options_menu = malloc(sizeof(OptionsMenu));
            //     if (state->options_menu != NULL) {
            //         init_options_menu(state->options_menu);
            //     } else {
            //         fprintf(stderr, "Nem sikerült memóriát foglalni a beállítások menünek!\n");
            //         // Kezeld a hibát megfelelően
            //     }
            // } else {
            //     // Ha már létezik a beállítások menü, esetleg visszaállítjuk az alapértelmezett kiválasztást
            //     state->options_menu->selected_option = 0;
            // }

            // 3. Egyéb állapotváltozók módosítása, amelyek a beállítások menü megjelenítését befolyásolják
            state->show_menu = false; // Például elrejthetjük a főmenüt a beállítások megjelenítésekor

            // 4. Hang effektek lejátszása
            // play_sound_effect(SFX_MENU_OPEN);

            // 5. Animációk indítása
            // start_menu_transition_animation(MENU_OPTIONS);
        }
        // És így tovább a többi menüponttal...
    }
}