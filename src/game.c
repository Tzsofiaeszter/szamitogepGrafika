#include <stdlib.h>
#include <SDL2/SDL.h>

#include "input.h"
#include "game.h"
#include "scene_manager.h"
#include "game_state.h"


static GameState* state = NULL;
static Menu* menu = NULL;
static SceneManager* manager = NULL;
static bool running = true;
static int brightness = 255;
static bool show_help = false;

void game_init() {
    manager = scene_manager_create();
    input_init(state, menu);
    if (!manager) exit(1);
}

void game_update() {
    scene_manager_update(manager);
}

void game_handle_event(SDL_Event* event) {
    if (event->type == SDL_QUIT) {
        running = false;
        return;
    }

    input_handle_event(event); 

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                game_state_set(state_main_menu, GAME_STATE_EXIT);
                running = false;
                break;
            case SDLK_h:
                show_help = !show_help;
                break;
            case SDLK_MINUS:
            case SDLK_KP_MINUS:
                brightness = (brightness > 10) ? brightness - 10 : 0;
                break;
        }
    }
}

bool game_is_running() {
    return running;
}
