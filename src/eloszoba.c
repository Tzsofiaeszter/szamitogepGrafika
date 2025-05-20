#include "game_state.h"
#include "eloszoba.h"

#include <stdio.h>
#include <string.h>

#define MAX_KOD_LENGTH 4

void eloszoba_init(Eloszoba* eloszoba) {
    if (eloszoba) {
        eloszoba->puzzle_solved = false;
        eloszoba->kod_length = 0;
        // Itt inicializálhatod az eloszoba további állapotát, textúrákat stb.
        // Például:
        // eloszoba->background_texture = loadTexture("textures/eloszoba_background.png");
        // ...
    }
}

void eloszoba_handle_event(SDL_Event* event, Eloszoba* eloszoba, char* kod_input, size_t* kod_length, GameState* game_state) {
    if (eloszoba && game_state) {
        if (event->type == SDL_TEXTINPUT) {
            if (*kod_length < MAX_KOD_LENGTH - 1) {
                kod_input[*kod_length] = event->text.text[0];
                (*kod_length)++;
                kod_input[*kod_length] = '\0';
                printf("Bevitt kód: %s\n", kod_input);
            }
        } else if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_RETURN) {
                printf("Kód ellenőrzése: %s\n", kod_input);
                // Itt végezheted el a kód ellenőrzését a helyes kóddal
                // Például, ha a helyes kód "1234":
                if (strcmp(kod_input, "1234") == 0) {
                    eloszoba->puzzle_solved = true;
                    printf("Helyes kód!\n");
                    game_state->current_scene= true; // Jelzi a GameState-nek, hogy a szoba megoldva
                } else {
                    printf("Hibás kód!\n");
                    // Opcionálisan: kód visszaállítása vagy más visszajelzés
                    *kod_length = 0;
                    kod_input[0] = '\0';
                }
            } else if (event->key.keysym.sym == SDLK_BACKSPACE && *kod_length > 0) {
                (*kod_length)--;
                kod_input[*kod_length] = '\0';
                printf("Kód visszavonva: %s\n", kod_input);
            }
        }
    }
}

void update_eloszoba(GameState* game_state) {
    // Itt frissítheted az eloszoba logikáját, ha van ilyen
    // Például animációk, objektumok mozgása stb.
    if (game_state && game_state->current_scene) {
        // Valami történhet, ha a szoba megoldott
        // Például egy ajtó kinyílhat, vagy egy új esemény indulhat
    }
}

void render_eloszoba(SDL_Renderer* renderer, Eloszoba* eloszoba) {
    if (renderer && eloszoba) {
        // Itt rajzolhatod ki az eloszoba elemeit a képernyőre
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Példa háttérszín
        SDL_RenderClear(renderer);

        // Példa a beírt kód kirajzolására (egyszerű szövegként)
        char kod_szoveg[MAX_KOD_LENGTH];
        strcpy(kod_szoveg, "Kód: ");
        //strcat(kod_szoveg, kod_input); // Ehhez a kod_input-ot át kellene adni a render függvénynek is

        // Valós implementációban textúrákat és rect-eket használnál a grafikus elemekhez
        // Például:
        // SDL_RenderCopy(renderer, eloszoba->background_texture, NULL, NULL);
        // ...

        SDL_RenderPresent(renderer);
    }
}

void cleanup_eloszoba(Eloszoba* eloszoba) {
    if (eloszoba) {
        // Itt szabadítsd fel az eloszobához tartozó erőforrásokat, pl. textúrákat
        // Például:
        // SDL_DestroyTexture(eloszoba->background_texture);
        // ...
    }
}