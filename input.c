#include "input.h"
#include "game_state.h"
#include "menu.h"

void handle_input(SDL_Event* event, GameState* state, Menu* menu) {
    if (event->type == SDL_QUIT) {
        state->running = false;
    } 
    else if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                state->running = false;
                break;
            case SDLK_h:
                state->show_help = !state->show_help;
                break;
            case SDLK_m:
                state->show_minimap = !state->show_minimap;
                break;
            case SDLK_w:
            case SDLK_UP:
                menu_move_up(menu);  // ha menüben vagy
                break;
            case SDLK_s:
            case SDLK_DOWN:
                menu_move_down(menu); 
                break;
            case SDLK_RETURN:
                menu_select(menu, state);  // választás
                break;
        }
    }
}
