#include <string.h>
#include "menu.h"
#include "game_state.h"
#include "ui.h"          //// ui_render_text miatt

void menu_init(Menu* menu) {
    menu->state = MENU_MAIN;
    menu->selected_item = 0;
    menu->items[0] = "Jatek inditasa";
    menu->items[1] = "Kilepes";
    menu->items[2] = NULL;
}

void menu_handle_input(Menu* menu, SDL_Event* event, int* running, bool* start_game) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                menu->selected_item = (menu->selected_item - 1 + 2) % 2;
                break;
            case SDLK_DOWN:
                menu->selected_item = (menu->selected_item + 1) % 2;
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

void render_menu(SDL_Renderer* renderer, TTF_Font* font, Menu* menu) {
    const char* options[] = { "1. Játék indítása", "2. Súgó", "3. Térkép", "4. Kilépés" };
    SDL_Color normal = { 255, 255, 255, 255 };
    SDL_Color selected = { 0, 255, 0, 255 };

    for (int i = 0; i < 4; i++) {
        int y = 100 + i * 50;
        SDL_Color color = (i == menu->selected_index) ? selected : normal;
        ui_render_text_colored(renderer, font, options[i], 100, y, color);
    }
}


void menu_select(Menu* menu, GameState* state) {
    switch (menu->selected_index) {
        case 0: // Játék indítása
            state->current_state = GAME_STATE_PLAYING;
            break;
        case 1: // Súgó
            state->current_state = GAME_STATE_HELP;
            break;
        case 2: // Térkép (opcionális: be/ki kapcsol)
            state->show_minimap = !state->show_minimap;
            break;
        case 3: // Kilépés
            state->running = false;
            break;
    }
}