#ifndef PUZZLE_LOGIC_H
#define PUZZLE_LOGIC_H

#include "puzzle.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef enum {
    ELLOSZOBA = 0,
    NAPPALI,
    HALOSZOBA,
    FURDO,
    ROOM_COUNT
} RoomID;

typedef struct {
    bool is_open;
} Door;

typedef struct {
    bool solved_rooms[ROOM_COUNT];
    bool accessible_rooms[ROOM_COUNT];
    Door doors[ROOM_COUNT];
    bool exit_game;
} PuzzleGameState;  // <-- Eredetileg: GameState

typedef struct {
    RoomID room_id;
    Puzzle* puzzle;
} PuzzleRoom;

void puzzle_room_init(PuzzleRoom* room, RoomID id, PuzzleType type);
void puzzle_room_update(PuzzleRoom* room, PuzzleGameState* state);
void puzzle_room_render(PuzzleRoom* room, SDL_Renderer* renderer);
void puzzle_room_handle_input(PuzzleRoom* room, PuzzleGameState* state, const SDL_Event* event);
void puzzle_room_cleanup(PuzzleRoom* room);

#endif
