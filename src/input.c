#include "input.h"
#include "render.h"
#include "menu.h"

#include <SDL2/SDL.h>

// Billentyűállapot frissítése
void key_state_update(SDL_Event* event, KeyState* key_state) {
    bool pressed = (event->type == SDL_KEYDOWN);
    SDL_Keycode key = event->key.keysym.sym;

    switch (key) {
        case SDLK_ESCAPE: key_state->escape = pressed; break;
        case SDLK_h:      key_state->h = pressed; break;
        case SDLK_w:      key_state->w = pressed; break;
        case SDLK_s:      key_state->s = pressed; break;
        case SDLK_a:      key_state->a = pressed; break;
        case SDLK_d:      key_state->d = pressed; break;
        case SDLK_UP:     key_state->up = pressed; break;
        case SDLK_DOWN:   key_state->down = pressed; break;
        case SDLK_RETURN: key_state->enter = pressed; break;
        case SDLK_PLUS:
        case SDLK_KP_PLUS: key_state->plus = pressed; break;
        case SDLK_MINUS:
        case SDLK_KP_MINUS: key_state->minus = pressed; break;
    }
}

bool key_state_is_pressed(KeyState* key_state, SDL_Keycode key) {
    switch (key) {
        case SDLK_ESCAPE: return key_state->escape;
        case SDLK_h:      return key_state->h;
        case SDLK_w:      return key_state->w;
        case SDLK_s:      return key_state->s;
        case SDLK_a:      return key_state->a;
        case SDLK_d:      return key_state->d;
        case SDLK_UP:     return key_state->up;
        case SDLK_DOWN:   return key_state->down;
        case SDLK_RETURN: return key_state->enter;
        case SDLK_PLUS:
        case SDLK_KP_PLUS: return key_state->plus;
        case SDLK_MINUS:
        case SDLK_KP_MINUS: return key_state->minus;
        default: return false;
    }
}

void input_init(InputContext* ctx, GameState* state, Menu* menu, Camera* camera, App* app) {
    ctx->key_state = (KeyState){0};
    ctx->game_state = state;
    ctx->menu = menu;
    ctx->camera = camera;
    ctx->app = app;
}

void input_handle_event(InputContext* ctx, const SDL_Event* event) {
    key_state_update((SDL_Event*)event, &ctx->key_state);

    if (event->type == SDL_QUIT) {
        ctx->game_state->running = false;
    }

    if (event->type == SDL_KEYDOWN) {
        if (ctx->key_state.escape) ctx->game_state->running = false;
        if (ctx->key_state.h) ctx->game_state->show_help = !ctx->game_state->show_help;

        // Menü navigáció
        if (ctx->key_state.w || ctx->key_state.up) menu_move_up(ctx->menu);
        if (ctx->key_state.s || ctx->key_state.down) menu_move_down(ctx->menu);
        if (ctx->key_state.enter) menu_select(ctx->menu, ctx->game_state);

        // Fényerő
        if (ctx->key_state.plus && ctx->app->brightness < 255) ctx->app->brightness += 10;
        if (ctx->key_state.minus && ctx->app->brightness > 0) ctx->app->brightness -= 10;

        // Kamera
        if (ctx->key_state.a) ctx->camera->x -= 10;
        if (ctx->key_state.d) ctx->camera->x += 10;
        if (ctx->key_state.w) ctx->camera->y -= 10;
        if (ctx->key_state.s) ctx->camera->y += 10;
    }
}
