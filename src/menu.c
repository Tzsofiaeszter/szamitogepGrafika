#include "menu.h"
#include "game_state.h"

#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>

/*
Inicializálja a Menü struktúrát alapértelmezett értékekkel.
Beállítja az induló állapotot, az elérhető menüpontokat, azok számát és megjelenítési jellemzőit.
*/
    void menu_init(Menu* menu) {
          if (menu) {
            menu->selected_item = MENU_ITEM_PLAY;   // Kezdő menüpont
    }
}

/*
Feldolgozza a billentyűleütéseket a menüben való navigáláshoz.
A fel/le gombokkal mozgatja a kijelölést, Enterrel kiválasztja a pontot.

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
*/

//Egyet lép vissza a menüpontok között (nem forgó).
    void menu_move_up(Menu* menu) {
          if (menu) {
            if (menu->selected_item > MENU_ITEM_PLAY) {
            menu->selected_item--;
        } else {
        menu->selected_item = MENU_ITEM_EXIT;                       // Vissza az utolsóra
    }
    printf("Selected menu item: %d\n", menu->selected_item);        // Debug
    }
}
    

//Egyet lép előre a menüpontok között (nem forgó).
    void menu_move_down(Menu* menu) {
        if (menu){
            if (menu->selected_item < MENU_ITEM_EXIT) {
            menu->selected_item++;
        }else {
        menu->selected_item = MENU_ITEM_PLAY; // Vissza az elsőre
    }
    printf("Selected menu item: %d\n", menu->selected_item); // Debug
        }
    }  

/*
A kiválasztott menüpont szövegének megfelelően módosítja a játék állapotát.
pl. elindítja a játékot, megjeleníti a súgót, kilép, stb.
*/
    void menu_select(Menu* menu, GameState* game_state) {
        if (!menu || !game_state) return;

        switch (menu->selected_item) {
        case MENU_ITEM_PLAY:
            game_state_set(game_state, GAME_STATE_PLAYING);         // Indítsa a játékot
            printf("Játék indítása!\n");                            // Debug
            break;
        case MENU_ITEM_HELP:
            game_state_set(game_state, GAME_STATE_HELP);            // Súgó megjelenítése
            printf("Súgó!\n");                                      // Debug
            break;
        case MENU_ITEM_EXIT:
            game_state_set(game_state, GAME_STATE_EXIT);            // Kilépés
            printf("Kilépés!\n");                                   // Debug
            break;
        default:
            break;
    }
}
