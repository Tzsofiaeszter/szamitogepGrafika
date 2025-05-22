#ifndef PUZZLE_LOGIC
#define PUZZLE_LOGIC
#include "game_state.h"   // fontos!
#include "puzzle.h"

typedef struct {
    RoomID room_id;
    Puzzle* puzzle;
    bool puzzle_solved;
} PuzzleRoom;

void puzzle_room_init(PuzzleRoom* room, RoomID id, PuzzleType type);
void puzzle_room_update(PuzzleRoom* room, GameState* state);
void puzzle_room_render(PuzzleRoom* room, SDL_Renderer* renderer);
void puzzle_room_handle_input(PuzzleRoom* room, GameState* state, const SDL_Event* event);
void puzzle_room_destroy(PuzzleRoom* room);

#endif