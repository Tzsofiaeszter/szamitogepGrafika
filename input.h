#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "game_state.h"
#include "menu.h"

void handle_input(SDL_Event* event, GameState* state, Menu* menu);

#endif // INPUT_H