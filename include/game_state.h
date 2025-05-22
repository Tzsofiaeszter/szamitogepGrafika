#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>
#include "eloszoba.h"

#define MAX_ROOMS 4

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_HELP,
    GAME_STATE_EXIT,
    GAME_STATE_ELOSZOBA, 
    GAME_STATE_COUNT
} GameStateEnum;

// Enum a szobák azonosításához (ha még nincsenek máshol definiálva)
typedef enum {
    ELOSZOBA = 0,
    NAPPALI,
    KONYHA,
    FURDOSZOBA,
    ROOM_COUNT  
} RoomID;

// Struktúra az ajtók állapotának tárolására
typedef struct {
    bool is_open;
    // Hozzáadhatsz ide más ajtóval kapcsolatos tulajdonságokat, pl. "is_locked", "target_room_id", stb.
} Door;

// Előre deklaráció a függvény mutató típushoz
typedef void (*StateFunc)(struct GameState*);

// A játék állapotának tárolására szolgáló struktúra
typedef struct GameState {
    bool running;          // Játék futása
    bool show_help;        // Súgó megjelenítése
    int brightness;        // Fényerő

    StateFunc current_state_func;     // Függvény mutató az aktuális állapotkezelő függvényre
    GameStateEnum current_enum_state; // Enum az aktuális állapotról (pl. UI-hoz, logoláshoz)
    
    bool exit_game;
    bool solved_rooms[ROOM_COUNT];
    //DoorState doors[ROOM_COUNT];         
    bool accessible_rooms[ROOM_COUNT];
   
    // Áthelyezett állapotok a PuzzleGameState-ből
    Door doors[MAX_ROOMS];        // Jelzi, hogy az adott szoba ajtaja nyitva van-e
    RoomID current_room;

    Eloszoba eloszoba_data;           // Eloszoba specifikus adatok

} GameState;

// Fgv.-ek deklarációi
void game_state_init(GameState* state);             // Állapot inicializálása
void game_state_set(GameState* state_obj, GameStateEnum new_state_enum);
void game_state_update_current(GameState* state);
void game_state_set_func(GameState* state, StateFunc new_state_func); // Új függvény a StateFunc beállítására


// Állapotfüggvények deklarációi
void state_main_menu(GameState* state); // Főmenü
void state_help(GameState* state);      // Súgó
void state_play(GameState* state);      // Játék
void state_eloszoba(GameState* state);  // Eloszoba állapot kezelője

#endif 
