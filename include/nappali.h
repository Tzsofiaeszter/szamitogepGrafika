/*#ifndef NAPPALI_H
#define NAPPALI_H

#include "puzzle_logic.h" // PuzzleRoom kell
#include "game_state.h"   // GameState kell
#include <SDL2/SDL.h>     // SDL_Event, SDL_Renderer kell

typedef struct {
    PuzzleRoom room; // A szoba puzzle-je
    // Később ide jönnének a nappali specifikus modellek, textúrák stb.
    // Model nappali_model;
    // GLuint carpet_texture;
    // ...
} NappaliData;

void nappali_init(NappaliData* nappali_data);
void nappali_render(const NappaliData* nappali_data, SDL_Renderer* renderer);
void nappali_handle_input(NappaliData* nappali_data, const SDL_Event* event, GameState* game_state);
void nappali_destroy(NappaliData* nappali_data);

#endif // NAPPALI_H
*/