#include "input.h"
#include "render.h"
#include"menu.h"
#include <SDL2/SDL.h>

void key_state_update(SDL_Event* event, KeyState* key_state) {
    bool pressed = (event->type == SDL_KEYDOWN);
    SDL_Keycode key = event->key.keysym.sym;

    switch (key) {
        case SDLK_ESCAPE: 
            key_state->escape = pressed; 
            break;
        case SDLK_h:        
            key_state->h = pressed; 
            break;
        case SDLK_w:        
            key_state->w = pressed; 
            break;
        case SDLK_s:      
            key_state->s = pressed; 
            break;
        case SDLK_a:      
            key_state->a = pressed; 
            break;
        case SDLK_d:      
            key_state->d = pressed; 
            break;
        case SDLK_UP:     
            key_state->up = pressed; 
            break;
        case SDLK_DOWN:   
            key_state->down = pressed; 
            break;
        case SDLK_RETURN: 
            key_state->enter = pressed; 
            break;
        case SDLK_PLUS:
        case SDLK_KP_PLUS:  
            key_state->plus = pressed; 
            break;
        case SDLK_MINUS:
        case SDLK_KP_MINUS: 
            key_state->minus = pressed; 
            break;
    }
}

bool key_state_is_pressed(KeyState* key_state, SDL_Keycode key) {
    switch (key) {
        case SDLK_ESCAPE: 
            return key_state->escape;
        case SDLK_h:      
            return key_state->h;
        case SDLK_w:      
            return key_state->w;
        case SDLK_s:      
            return key_state->s;
        case SDLK_a:      
            return key_state->a;
        case SDLK_d:      
            return key_state->d;
        case SDLK_UP:     
            return key_state->up;
        case SDLK_DOWN:   
            return key_state->down;
        case SDLK_RETURN: 
            return key_state->enter;
        case SDLK_PLUS:
        case SDLK_KP_PLUS: 
             return key_state->plus;
        case SDLK_MINUS:
        case SDLK_KP_MINUS: 
            return key_state->minus;
        default: return false;
    }
}

void handle_input(SDL_Event* event, GameState* state, Menu* menu, KeyState* key_state) {
    key_state_update(event, key_state);

    if (event->type == SDL_QUIT) {
        state->running = false;
    }

    if (event->type == SDL_KEYDOWN) {
        if (key_state->escape) state->running = false;
        if (key_state->h) state->show_help = !state->show_help;
       

        // Menüvezérlés
        if (key_state->w || key_state->up) menu_move_up(menu);
        if (key_state->s || key_state->down) menu_move_down(menu);
        if (key_state->enter) menu_select(menu, state);

        // Fényerő
        if (key_state->plus && brightness < 255) brightness += 10;
        if (key_state->minus && brightness > 0) brightness -= 10;

        // Kamera
        if (key_state->a) camera.x -= 10;
        if (key_state->d) camera.x += 10;
        if (key_state->w) camera.y -= 10;
        if (key_state->s) camera.y += 10;
    }
}



static KeyState key_state;
static GameState* game_state = NULL;
static Menu* menu_state = NULL;

void input_init(GameState* state, Menu* menu) {
    // Inicializáljuk a KeyState struktúrát nullára
    key_state = (KeyState){0};
    game_state = state;
    menu_state = menu;
}

void input_handle_event(const SDL_Event* event) {
    // Frissítjük a billentyűállapotot
    key_state_update((SDL_Event*)event, &key_state);

    if (event->type == SDL_QUIT) {
        game_state->running = false;
    }

    if (event->type == SDL_KEYDOWN) {
        if (key_state.escape) game_state->running = false;
        if (key_state.h) game_state->show_help = !game_state->show_help;

        // Menü navigáció
        if (key_state.w || key_state.up) menu_move_up(menu_state);
        if (key_state.s || key_state.down) menu_move_down(menu_state);
        if (key_state.enter) menu_select(menu_state, game_state);

        // Fényerő növelés/csökkentés
        if (key_state.plus && brightness < 255) brightness += 10;
        if (key_state.minus && brightness > 0) brightness -= 10;

        // Kamera mozgatás
        if (key_state.a) camera.x -= 10;
        if (key_state.d) camera.x += 10;
        if (key_state.w) camera.y -= 10;
        if (key_state.s) camera.y += 10;
    }
}
  