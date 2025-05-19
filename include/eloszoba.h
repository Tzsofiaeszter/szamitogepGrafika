#ifndef ELOSZOBA_H
#define ELOSZOBA_H

#include "game_state.h"
#include "puzzle.h"
#include "eloszoba.h"

#include <stdbool.h>
#include <SDL2/SDL.h>



typedef struct {
    bool puzzle_solved;
    size_t kod_length;
    SDL_Texture* background_texture;
    SDL_Texture* kod_szamok_texture[10];
    SDL_Rect kod_szamok_rect[10];
    //SDL_Texture* kod_helyek_texture[MAX_KOD_LENGTH];
    //SDL_Rect kod_helyek_rect[MAX_KOD_LENGTH];
    SDL_Texture* enter_gomb_texture;
    SDL_Rect enter_gomb_rect;
    //bool kod_helyek_elerheto[MAX_KOD_LENGTH];
    //int correct_code[MAX_KOD_LENGTH];
    int kod_hossz;
} Eloszoba;



// Inicializálja az eloszoba állapotát
void eloszoba_init(Eloszoba* eloszoba);

// Kezeli az eloszobában történt eseményeket (pl. billentyűzet, egér)
void eloszoba_handle_event(SDL_Event* event, Eloszoba* eloszoba, char* kod_input, size_t* kod_length, GameState* game_state);
// Frissíti az eloszoba logikáját (pl. animációk, állapotváltozások)
void update_eloszoba(GameState* game_state);

// Kirajzolja az eloszoba elemeit a képernyőre
void render_eloszoba(SDL_Renderer* renderer, Eloszoba* eloszoba);

// Felszabadítja az eloszobához tartozó erőforrásokat
void cleanup_eloszoba(Eloszoba* eloszoba);

#endif 
