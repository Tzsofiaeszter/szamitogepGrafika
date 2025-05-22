#ifndef ELOSZOBA_H
#define ELOSZOBA_H


#include <SDL2/SDL.h>
#include <stdbool.h>
//#include "game_state.h"
//#include "puzzle.h"

struct GameState;
#define MAX_KOD_LENGTH 4

typedef struct Eloszoba {
    bool puzzle_solved;
    size_t kod_length;
    char kod_input[MAX_KOD_LENGTH + 1];          // A bevitt kód tárolására
    /*SDL_Texture* background_texture;
    SDL_Texture* kod_szamok_texture[10];
    SDL_Rect kod_szamok_rect[10];
    //SDL_Texture* kod_helyek_texture[MAX_KOD_LENGTH];
    //SDL_Rect kod_helyek_rect[MAX_KOD_LENGTH];
    SDL_Texture* enter_gomb_texture;
    SDL_Rect enter_gomb_rect;
    //bool kod_helyek_elerheto[MAX_KOD_LENGTH];
    //int correct_code[MAX_KOD_LENGTH];
    int kod_hossz;*/

} Eloszoba;

// Függvény deklarációk
void eloszoba_init(Eloszoba* eloszoba);
void eloszoba_handle_event(SDL_Event* event, Eloszoba* eloszoba, char* kod_input, size_t* kod_length, struct GameState* game_state);
void render_eloszoba(SDL_Renderer* renderer, Eloszoba* eloszoba);
void eloszoba_reset(Eloszoba* eloszoba);
void update_eloszoba(struct GameState* game_state); // Itt is struct GameState*

#endif 
