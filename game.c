#include "game.h"
#include "scene_manager.h"
#include "ui.h"
#include <stdlib.h>

static SceneManager* manager = NULL;

// globális változók!!!
bool show_help = false;
bool show_minimap = false;
bool running = true;
int brightness = 255; // Alapértelmezett fényerő, teljes világosság

typedef enum GameState {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_HELP,
    GAME_STATE_EXIT
} GameState;

GameState current_state = GAME_STATE_MENU; // Kezdetben a játék a menüben van

void game_init() {
    manager = scene_manager_create();
    if (!manager) exit(1);
}

void game_update() {
    scene_manager_update(manager);
}

void game_render(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    scene_manager_render(manager, renderer, font);
    render_help_overlay(renderer, font, 800, 600, show_help);

    const char* room_names[4] = {"Északi", "Keleti", "Déli", "Nyugati"};
    ui_render_minimap_overlay(renderer, font, manager->current_room, manager->solved_rooms, 800, 600, show_minimap, room_names);

    SDL_RenderPresent(renderer);
}

void game_cleanup() {
    scene_manager_free(manager);
}

bool game_is_running() {
    return running;
}

void game_handle_event(SDL_Event* event) {
    // Kilépés az alkalmazásból
    if (event->type == SDL_QUIT) {
        running = false;
    } 
    // Billentyűleütések kezelése
    else if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            // Kilépés
            case SDLK_ESCAPE:
                current_state = GAME_STATE_EXIT; // Kilépés
                break;

            // Segítség megjelenítése
            case SDLK_h:
                if (current_state == GAME_STATE_PLAYING) {
                    current_state = GAME_STATE_HELP;  // Segítség megjelenítése játék közben
                } else if (current_state == GAME_STATE_HELP) {
                    current_state = GAME_STATE_PLAYING;  // Vissza a játékba
                }
                break;

            // Térkép váltása
            case SDLK_m:
                if (current_state == GAME_STATE_PLAYING) {
                    show_minimap = !show_minimap;  // Toggle minimap
                }
                break;

            // Nyilakkal vagy 'w', 's' billentyűkkel történő navigáció menüben
            case SDLK_UP:
            case SDLK_w:
                if (current_state == GAME_STATE_MENU) {
                    // Navigálás fel
                }
                break;

            case SDLK_DOWN:
            case SDLK_s:
                if (current_state == GAME_STATE_MENU) {
                    // Navigálás le
                }
                break;

            // Menü kiválasztás (ENTER)
            case SDLK_RETURN:
                if (current_state == GAME_STATE_MENU) {
                    // Menüpont választás (játék indítása, súgó, stb.)
                }
                break;

            // Fényerő növelése
            case SDLK_PLUS:
            case SDLK_KP_PLUS:
                brightness += 10;  // Fényerő növelése
                if (brightness > 255) brightness = 255;
                break;

            // Fényerő csökkentése
            case SDLK_MINUS:
            case SDLK_KP_MINUS:
                brightness -= 10;  // Fényerő csökkentése
                if (brightness < 0) brightness = 0;
                break;

            // Mozgás billentyűk
            case SDLK_w:
                if (current_state == GAME_STATE_PLAYING) {
                    input_state.move_up = true;  // Felfelé mozgás
                }
                break;
            case SDLK_a:
                if (current_state == GAME_STATE_PLAYING) {
                    input_state.move_left = true;  // Balra mozgás
                }
                break;
            case SDLK_s:
                if (current_state == GAME_STATE_PLAYING) {
                    input_state.move_down = true;  // Lefelé mozgás
                }
                break;
            case SDLK_d:
                if (current_state == GAME_STATE_PLAYING) {
                    input_state.move_right = true;  // Jobbra mozgás
                }
                break;
        }
    } 
    // Billentyű felengedésének kezelése (mozgás leállítása)
    else if (event->type == SDL_KEYUP) {
        switch (event->key.keysym.sym) {
            case SDLK_w:
                input_state.move_up = false;
                break;
            case SDLK_a:
                input_state.move_left = false;
                break;
            case SDLK_s:
                input_state.move_down = false;
                break;
            case SDLK_d:
                input_state.move_right = false;
                break;
        }
    }
}

 