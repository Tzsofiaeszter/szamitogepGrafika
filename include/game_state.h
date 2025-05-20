#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>
#include "game_state.h"
//#include "menu.h"
//#include "puzzle.h"
//#include "puzzle_logic.h"

// Enum a játék állapotokhoz
typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAY,
    GAME_STATE_HELP,
    GAME_STATE_EXIT,
} GameStateEnum;

typedef enum {
    SCENE_MENU,     // Ha van menü állapotod
    SCENE_GAME,
    SCENE_HELP,
    SCENE_OPTIONS,
} SceneState;

// A játék állapotának tárolására szolgáló struktúra
typedef struct  {
    bool running;      // Játék futása
    bool show_help;    // Súgó megjelenítése
    int brightness;    // Fényerő
    SceneState current_scene; 
    bool is_options_menu_active; 
    bool show_menu;
    //PuzzleGameState puzzle_state;
} GameState;

void game_state_set(void (*new_state)(GameState*), GameStateEnum enum_state);


// Funkciók deklarációi
void game_state_init(GameState* state);                // Állapot inicializálása
void game_state_update(GameState* state);              // Játék frissítése az aktuális állapotnak megfelelően
GameStateEnum game_state_get_enum();                      // Aktuális állapot lekérdezése

// Állapotfüggvények deklarációi
void state_main_menu(GameState* state); // Főmenü
void state_help(GameState* state);      // Súgó
void state_play(GameState* state);      // Játék
void state_exit(GameState* state);

#endif // GAME_STATE_H
