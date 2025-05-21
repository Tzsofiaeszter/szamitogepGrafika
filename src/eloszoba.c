#include "game_state.h"
#include "eloszoba.h"

#include <stdio.h>
#include <string.h>

#define MAX_KOD_LENGTH 4

/*
Előszoba állapotának inicializálása
 - Beállítja a puzzle megoldottságát hamisra
 - Kezdetben üres a bevitt kód (hossz 0)
 - (Opcionálisan: textúrák, grafikai elemek betöltése)
*/
    void eloszoba_init(Eloszoba* eloszoba) {
        if (eloszoba) {
            eloszoba->puzzle_solved = false;
            eloszoba->kod_length = 0;
            // Itt inicializálhatom még az eloszoba további állapotát, textúrákat stb.
            // Például:
            // eloszoba->background_texture = loadTexture("textures/eloszoba_background.png");
            // ...
        }
    }

/*
Felhasználói események kezelése az előszobában
 - Szövegbevitel: karakterek hozzáadása a kódhoz
 - ENTER: kód ellenőrzése (ha helyes, puzzle megoldva)
 - BACKSPACE: utolsó karakter törlése
 - Frissíti a GameState-et is, ha a feladvány megoldott
*/    
    void eloszoba_handle_event(SDL_Event* event, Eloszoba* eloszoba, char* kod_input, size_t* kod_length, GameState* game_state) {
        if (eloszoba && game_state) {
            if (event->type == SDL_TEXTINPUT) {
                if (*kod_length < MAX_KOD_LENGTH - 1) {
                    kod_input[*kod_length] = event->text.text[0];
                    (*kod_length)++;
                    kod_input[*kod_length] = '\0';
                    printf("Bevitt kod: %s\n", kod_input);
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
/*
Előszoba logikájának frissítése
 - Itt végezhető el minden, ami a játékállapot frissítéséhez szükséges
 - Például: animációk, állapotváltozások, ha a puzzle megoldott
*/
    void update_eloszoba(GameState* game_state) {
        // Itt frissíthetem az eloszoba logikáját, ha van ilyen
        // Például animációk, objektumok mozgása stb.
        if (game_state && game_state->current_scene) {
            // Valami történhet, ha a szoba megoldott
            // Például egy ajtó kinyílhat, vagy egy új esemény indulhat
        }
    }

/*
Előszoba kirajzolása
 - Tisztítja a képernyőt
 - (Jelenleg csak a háttérszín van beállítva)
 - Később: textúrák, objektumok megjelenítése
 - (A beírt kód kirajzolásához a kod_input-ot is át kellene adni)
*/    
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

/*
Előszoba erőforrásainak felszabadítása
 - Itt szabadíthatod fel a betöltött textúrákat, memóriát stb.
*/
    void cleanup_eloszoba(Eloszoba* eloszoba) {
        if (eloszoba) {
            // Itt szabadítsd fel az eloszobához tartozó erőforrásokat, pl. textúrákat
            // Például:
            // SDL_DestroyTexture(eloszoba->background_texture);
            // ...
        }
    }