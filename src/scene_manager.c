#include "scene_manager.h"
#include "game_state.h"
#include "eloszoba.h"
#include "puzzle.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

    const char* room_names[4] = { "Eloszoba", "Nappali", "Konyha", "Furdoszoba"};

/* 
SceneManager létrehozása és inicializálása. 
Lefoglalja a memóriát, beállítja az első szobát (Előtér), 
inicializálja a hozzá tartozó rejtvényt és eseménykezelőket. 
*/
    SceneManager* scene_manager_create() {
    SceneManager* manager = malloc(sizeof(SceneManager));
    if (!manager) {
        fprintf(stderr, "Nem sikerült memóriát foglalni a SceneManager számára!\n");
        return NULL;
    }

    manager->current_room_id = ELOSZOBA; // Kezdetben az előszoba
    manager->total_rooms = NUM_ROOMS; // A ROOM_ID enum mérete

    // Szobák inicializálása
    // Előszoba inicializálása
    eloszoba_init(&(manager->eloszoba_data));
    manager->rooms[ELOSZOBA].room_id = ELOSZOBA;
    manager->rooms[ELOSZOBA].puzzle = puzzle_create(PUZZLE_CODE_YEAR); // Példa: eloszoba puzzle típusa
    manager->rooms[ELOSZOBA].puzzle_solved = false;

    // nappali_init(&(manager->nappali_data));
    // manager->rooms[NAPPALI].room_id = NAPPALI;
    // manager->rooms[NAPPALI].puzzle = puzzle_create(PUZZLE_WORD_ORDER);
    // manager->rooms[NAPPALI].puzzle_solved = false;

    // Inicializálja az összes puzzle-t (ha a GameState kezeli a puzzle-ket)
    // for (int i = 0; i < NUM_ROOMS; ++i) {
    //     puzzle_room_init(&(manager->rooms[i]), (RoomID)i, PUZZLE_LOGIC); // Alapértelmezett logika
    // }

    return manager;
}

/*
SceneManager felszabadítása. 
Felszabadítja az összes rejtvényhez tartozó memóriát, 
valamint a szobákhoz tartozó erőforrásokat is.
*/
  void scene_manager_update(SceneManager* manager, GameState* game_state) {
    if (!manager || !game_state) return;

    // Frissíti az aktuális szoba puzzle-jét
    if (manager->rooms[manager->current_room_id].puzzle) {
        puzzle_room_update(&(manager->rooms[manager->current_room_id]), game_state);
    }
}

    void scene_manager_render(const SceneManager* manager, SDL_Renderer* renderer) {
        if (!manager || !renderer) return;

        // Rendereli a jelenlegi szobát
        // Ezt a render_app hívja meg, ami majd a game_state alapján dönti el, mit renderel
        // Pl. render_eloszoba, render_nappali, stb.
        // printf("Aktuális szoba: %s\n", room_names[manager->current_room_id]); // Debug
        if (manager->rooms[manager->current_room_id].puzzle) {
            puzzle_room_render(&(manager->rooms[manager->current_room_id]), renderer);
        }
    }

/*
A következő szobára léptet, ha van még további szoba. 
(Jelenleg csak 1 van, így nincs hatása.)

    void scene_manager_next_room(SceneManager* manager) {
        if (manager->current_room < manager->total_rooms - 1) {
            manager->current_room++;
        }
    }
*/

/*
A jelenlegi szoba állapotának frissítése.
Ha van rejtvény és az még nincs megoldva, bekéri a felhasználó válaszát
és megpróbálja megoldani vele a rejtvényt.
*/
    void scene_manager_update(SceneManager* manager) {
        if (manager->current_room == 0)
        {
            return;   //mivel már az eseménykezelő megoldja a logikát
        }

        Puzzle* puzzle = manager->rooms[manager->current_room].puzzle;
        if (!manager->rooms[manager->current_room].puzzle_solved && puzzle) {
            char input[64];
            printf(">> ");
            if (scanf("%63s", input) == 1) {
                if (puzzle->solve(puzzle, input)) {
                    printf("Puzzle megoldva!\n");
                    manager->rooms[manager->current_room].puzzle_solved = true;
                } else {
                    printf("Hibás válasz. Próbáld újra!\n");
                }
            } else {
                // Hiba a beolvasás során
                while (getchar() != '\n'); // Puffer ürítése
            }
        }
    }

/*
SDL események kezelése a jelenlegi szobában.
Jelenleg csak az előtér eseményeit kezeli (pl. szövegbevitel),
és ha sikerül a rejtvényt megoldani, azt eltárolja.
*/

void scene_manager_handle_event(SceneManager* manager, const SDL_Event* event, GameState* game_state) {
    if (!manager || !event || !game_state) return;

    // Átadja az eseményt a jelenlegi szoba input kezelőjének
    // Ennek a függvénynek már csak az adott szoba specifikus inputját kellene kezelnie
    // Az általános inputot (ESC, H, +/-) az input.c kezeli.

    // Fontos: az SDL_StartTextInput() és SDL_StopTextInput() az app.c-ben kellene,
    // amikor az állapot GAME_STATE_ELOSZOBA vagy hasonló.
    // Itt csak az adott szoba specifikus eseménykezelőjét hívjuk:
    // Pl. eloszoba_handle_event ha az aktuális szoba az eloszoba.

    if (manager->current_room_id == ELOSZOBA) {
        // eloszoba_handle_event már megkapja az eloszoba_data-t a game_state-ből
        // és kezeli a kód bevitelt.
        // SDL_StartTextInput() / SDL_StopTextInput() kellene az app.c-ben
        // amikor az állapot Eloszoba (TEXTINPUT kell) vagy elhagyjuk (TEXTINPUT nem kell)
        // A hívás már az input.c-ben megtörténik, így itt már nem kell.
        // eloszoba_handle_event((SDL_Event*)event, &(game_state->eloszoba_data), game_state);
        puzzle_room_handle_input(&(manager->rooms[ELOSZOBA]), event, game_state);
    }

/*
Felszabadítja a SceneManager által lefoglalt erőforrásokat.
*/
void scene_manager_destroy(SceneManager* manager) {
    if (manager) {
        // Felszabadítja az összes szoba puzzle-jét
        for (int i = 0; i < manager->total_rooms; ++i) {
            puzzle_destroy(manager->rooms[i].puzzle);
        }
        free(manager);
    }
}