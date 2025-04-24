#include "game_state.h"

void game_state_init(GameState* state) {
    state->running = true;
    state->show_help = false;
    state->show_minimap = false;
    state->brightness = 255; // maximális fényerő induláskor
}