#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "menu.h"
#include "game_state.h"

typedef struct {
    bool escape, h, w, s, a, d, up, down, enter;
    bool plus, minus;
} KeyState;

void key_state_update(SDL_Event* event, KeyState* key_state);
bool key_state_is_pressed(KeyState* key_state, SDL_Keycode key);
void handle_input(SDL_Event* event, GameState* state, Menu* menu, KeyState* key_state);

void input_init(GameState* state, Menu* menu);
void input_handle_event(const SDL_Event* event);


#endif

