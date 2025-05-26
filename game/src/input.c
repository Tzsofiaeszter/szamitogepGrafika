/*
#include "input.h"
#include "light.h"

#include <stdio.h>

void input_init(InputContext* ctx, void* unused1, void* unused2, Camera* camera, App* app) {
    ctx->key_state = (KeyState){0};
    ctx->camera = camera;
    ctx->app = app;
}

void key_state_update(SDL_Event* event, KeyState* key_state) {
    bool pressed = (event->type == SDL_KEYDOWN);
    SDL_Keycode key = event->key.keysym.sym;

    switch (key) {
        case SDLK_ESCAPE: 
            key_state->escape = pressed; 
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
        case SDLK_F1:     
            key_state->F1 = pressed; 
            break;
        case SDLK_PLUS:
        case SDLK_KP_PLUS:  
            key_state->plus = pressed; 
            break;
        case SDLK_MINUS:
        case SDLK_KP_MINUS: 
            key_state->minus = pressed; 
            break;
    
      // Fény mozgatása (pl. IJKLUO)
        case SDLK_j: 
            key_state->move_light_x_neg = pressed; 
            break;
        case SDLK_l: 
            key_state->move_light_x_pos = pressed; 
            break;
        case SDLK_k: 
            key_state->move_light_y_neg = pressed; 
            break;
        case SDLK_i: 
            key_state->move_light_y_pos = pressed; 
            break;
        case SDLK_u:    
            key_state->move_light_z_neg = pressed; 
            break;
        case SDLK_o: 
            key_state->move_light_z_pos = pressed; 
            break;
    }
}

void input_handle_event(InputContext* ctx, const SDL_Event* event) {
    key_state_update((SDL_Event*)event, &ctx->key_state);

    if (event->type == SDL_QUIT) {
            printf("[DEBUG] SDL_QUIT esemény érkezett\n");
        ctx->app->is_running = false;
    }

    if (event->type == SDL_KEYDOWN) {
            printf("[DEBUG] KEYDOWN: %s\n", SDL_GetKeyName(event->key.keysym.sym));

        if (ctx->key_state.escape) ctx->app->is_running = false;

        if (ctx->key_state.w) set_camera_speed(ctx->camera, 1);
        if (ctx->key_state.s) set_camera_speed(ctx->camera, -1);
        if (ctx->key_state.a) set_camera_side_speed(ctx->camera, 1);
        if (ctx->key_state.d) set_camera_side_speed(ctx->camera, -1);

        if (ctx->key_state.F1)
            ctx->camera->is_preview_visible = !(ctx->camera->is_preview_visible);

        if (ctx->key_state.plus) {
            ctx->app->brightness += 10;
            if (ctx->app->brightness > 255) ctx->app->brightness = 255;
            set_light_brightness(&(ctx->app->scene.light), ctx->app->brightness);
        }

        if (ctx->key_state.minus) {
            ctx->app->brightness -= 10;
            if (ctx->app->brightness < 0) ctx->app->brightness = 0;
            set_light_brightness(&(ctx->app->scene.light), ctx->app->brightness);
        }

        // FÉNY MOZGATÁS (light.position[] manipulálása)
        if (ctx->key_state.move_light_x_neg) ctx->app->scene.light.position[0] -= 0.2f;
        if (ctx->key_state.move_light_x_pos) ctx->app->scene.light.position[0] += 0.2f;
        if (ctx->key_state.move_light_y_neg) ctx->app->scene.light.position[1] -= 0.2f;
        if (ctx->key_state.move_light_y_pos) ctx->app->scene.light.position[1] += 0.2f;
        if (ctx->key_state.move_light_z_neg) ctx->app->scene.light.position[2] -= 0.2f;
        if (ctx->key_state.move_light_z_pos) ctx->app->scene.light.position[2] += 0.2f;

        glLightfv(ctx->app->scene.light.id, GL_POSITION, ctx->app->scene.light.position);
    }

    if (event->type == SDL_KEYUP) {
        SDL_Keycode key = event->key.keysym.sym;

        if (key == SDLK_w || key == SDLK_s)
            set_camera_speed(ctx->camera, 0);

        if (key == SDLK_a || key == SDLK_d)
            set_camera_side_speed(ctx->camera, 0);
    }

    if (event->type == SDL_MOUSEBUTTONDOWN) {
        ctx->app->mouse_down = true;
    }

    if (event->type == SDL_MOUSEBUTTONUP) {
        ctx->app->mouse_down = false;
    }

    if (event->type == SDL_MOUSEMOTION && ctx->app->mouse_down) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        rotate_camera(ctx->camera, ctx->app->mouse_x - x, ctx->app->mouse_y - y);
        ctx->app->mouse_x = x;
        ctx->app->mouse_y = y;
    }
}

*/
