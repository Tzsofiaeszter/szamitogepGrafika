#pragma once   // - a fordítás során csak eygsezr szabad felhasználni

#include <SDL2/SDL.h>

// Új struktúra a játék globális állapotának tárolására
typedef struct {
    GameState* state;
    Menu* menu;
    SceneManager* manager;
    bool running;
    int brightness;
    bool show_help;
} GameContext;

// Függvények szignatúrái
void game_init(GameContext* context);
void game_update(GameContext* context);
void game_handle_event(GameContext* context, SDL_Event* event); // event is paraméter
void game_render(const GameContext* context); // Ha van render függvény a game.c-ben
void game_cleanup(GameContext* context); // Új cleanup függvény
bool game_is_running(const GameContext* context); // Segédfüggvény a fő ciklushoz
