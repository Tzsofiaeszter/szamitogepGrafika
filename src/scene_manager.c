#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<SDL2/SDL.h>

#include "scene_manager.h"
#include "game_state.h"
#include "eloszoba.h"
#include "puzzle.h"

const char* room_names[4] = { "Eloszoba", "Nappali", "Konyha", "Furdoszoba"};


SceneManager* scene_manager_create() {
    SceneManager* manager = malloc(sizeof(SceneManager));
     if (!manager) {
        fprintf(stderr, "Nem sikerült memóriát foglalni a SceneManager számára!\n");
        return NULL;
    }
    manager->current_room = 0;
    manager->total_rooms = 1; // Egyelőre 1 szoba: előtér

    //char kod_input[] = "2025";
    
    manager->rooms[0].init = eloszoba_init;
    manager->rooms[0].render = render_eloszoba;
    manager->rooms[0].handle_input =  eloszoba_handle_event;
    manager->rooms[0].cleanup = cleanup_eloszoba;
    
// Szoba 1: előtér
    manager->rooms[0].puzzle = puzzle_create(PUZZLE_CODE_YEAR);
    if (!manager->rooms[0].puzzle) {
        fprintf(stderr, "Nem sikerült rejtvényt létrehozni az előszobához!\n");
        free(manager);
        return NULL;
    }

    manager->rooms[0].puzzle_solved = false;
    manager->rooms[0].name = "Előtér";

    manager->eloszoba.kod_length = 0;
    manager->kod_input[0] = '\0';
    eloszoba_init(&manager->eloszoba);

    return manager;
/*
 Szoba 2: nappali
    manager->rooms[1].puzzle = puzzle_create(PUZZLE_WORD_ORDER);
    manager->rooms[1].puzzle_solved = false;
    manager->rooms[1].name = "Nappali";
*/
}
    

void scene_manager_free(SceneManager* manager) {
    if (manager) {
        for (size_t i = 0; i < manager->total_rooms; ++i) {
            if (manager->rooms[i].puzzle) {
                free(manager->rooms[i].puzzle->data);
                free(manager->rooms[i].puzzle);
            }
            if (manager->rooms[i].cleanup) {
                manager->rooms[i].cleanup(&manager->eloszoba); 
            }
        }
        free(manager);
    }
}

void scene_manager_next_room(SceneManager* manager) {
    if (manager->current_room < manager->total_rooms - 1) {
        manager->current_room++;
    }
}

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


void scene_manager_handle_event(SceneManager* manager, SDL_Event* event, GameState* game_state) {
    if (manager->current_room == 0) {
        SDL_StartTextInput();
        eloszoba_handle_event(event, &manager->eloszoba, manager->kod_input, &manager->eloszoba.kod_length, game_state);        
        if (manager->eloszoba.puzzle_solved && !manager->rooms[0].puzzle_solved) {
            manager->rooms[0].puzzle_solved = true;
            printf("Előtér kód megoldva!\n");
        }
    } else {
        // további szobák eseménykezelése - továbbiakban
    }
}


