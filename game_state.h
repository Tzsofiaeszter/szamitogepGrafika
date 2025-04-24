#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>

// játék állapot struktúrája
typedef struct GameState{
    bool running;           // Futtat�si ciklus 
    bool show_help;         // Seg�ts�g overlay
    bool show_minimap;      // Minimap overlay
    int brightness;         // F�nyer�, 0-255
} GameState;

typedef enum GameMode{
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_HELP,
    GAME_STATE_EXIT
} GameMode;


// inicializálás
void game_state_init(GameState* state);

#endif
