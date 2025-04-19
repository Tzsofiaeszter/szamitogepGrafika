#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "game_state.h"
#include "input.h"
#include "menu.h"
#include "scene_manager.h"
#include "render.h"
#include "displayHelp.h"
#include "displayMinimap.h"
#include "ui.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Puzzle Game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("fonts/OpenSans-Regular.ttf", 24);

    if (!font) {
        SDL_Log("Hiba a betűtípus betöltésénél: %s", TTF_GetError());
        return 1;
    }

// Állapotok
    GameState game_state;
    game_state_init(&game_state);

    Menu menu;
    menu_init(&menu);

    SceneManager* scene_manager = scene_manager_create();

    SDL_Event event;

    while (game_state.running) {
        while (SDL_PollEvent(&event)) {
            handle_input(&event, &game_state, &menu);
        }

// Kirajzolás az állapot alapján
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (game_state.current_state) {
            case GAME_STATE_MENU:
                render_menu(renderer, font, &menu);
                break;

            case GAME_STATE_PLAYING:
                scene_manager_update(scene_manager);
                scene_manager_render(scene_manager, renderer, font);
                if (game_state.show_help) {
                    render_help_overlay(renderer, font, WINDOW_WIDTH, WINDOW_HEIGHT, true);
                }
                if (game_state.show_minimap) {
                    ui_render_minimap_overlay(renderer, font,
                                              scene_manager->current_room,
                                              scene_manager->solved_rooms,
                                              WINDOW_WIDTH, WINDOW_HEIGHT,
                                              true,
                                              scene_manager->room_names);
                }
                break;

            case GAME_STATE_HELP:
                render_help_overlay(renderer, font, WINDOW_WIDTH, WINDOW_HEIGHT, true);
                break;

            case GAME_STATE_EXIT:
                game_state.running = false;
                break;
        }

        SDL_RenderPresent(renderer);
    }

// Cleanup
    scene_manager_free(scene_manager);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

void handle_input(SDL_Event* event, GameState* game_state, Menu* menu) {
    if (event->type == SDL_QUIT) {
        game_state->running = false;
    }

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                game_state->running = false;
                break;
            case SDLK_h:
                game_state->show_help = !game_state->show_help;
                break;
            case SDLK_m:
                game_state->show_minimap = !game_state->show_minimap;
                break;
            case SDLK_UP:
            case SDLK_w:
                if (game_state->current_state == GAME_STATE_MENU) {
                    menu_move_up(menu);
                }
                break;
            case SDLK_DOWN:
            case SDLK_s:
                if (game_state->current_state == GAME_STATE_MENU) {
                    menu_move_down(menu);
                }
                break;
            case SDLK_RETURN:
                if (game_state->current_state == GAME_STATE_MENU) {
                    menu_select(menu, game_state);
                }
                break;
        }
    }
}
