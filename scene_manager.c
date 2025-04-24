#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scene_manager.h"

SceneManager* scene_manager_create() {
    SceneManager* manager = malloc(sizeof(SceneManager));
    manager->current_room = 0;
    manager->total_rooms = 2; // Egyelőre két szoba: előtér, nappali

    char kod_input[] = "2025";
    puzzle_try_solve(current_puzzle, kod_input);
    
    manager->rooms[0].init = eloszoba_init;
    manager->rooms[0].render = eloszoba_render;
    manager->rooms[0].handle_input = eloszoba_handle_input;
    manager->rooms[0].cleanup = eloszoba_cleanup;
    
    // Szoba 1: előtér
    manager->rooms[0].puzzle = puzzle_create(PUZZLE_CODE_YEAR);
    manager->rooms[0].puzzle_solved = false;
    manager->rooms[0].name = "Előtér";

    // Szoba 2: nappali
    manager->rooms[1].puzzle = puzzle_create(PUZZLE_SCISSOR_PILLOW);
    manager->rooms[1].puzzle_solved = false;
    manager->rooms[1].name = "Nappali";

    manager->eloszoba.kod_length = 0;
    manager->kod_input[0] = '\0';
    eloszoba_init(&manager->eloszoba);

    return manager;
}

void scene_manager_free(SceneManager* manager) {
    for (int i = 0; i < manager->total_rooms; ++i) {
        if (manager->rooms[i].puzzle) {
            free(manager->rooms[i].puzzle->data);
            free(manager->rooms[i].puzzle);
        }
    }
    free(manager);
}

void scene_manager_next_room(SceneManager* manager) {
    if (manager->current_room < manager->total_rooms - 1) {
        manager->current_room++;
    }
}

void scene_manager_render(SceneManager* manager, SDL_Renderer* renderer, TTF_Font* font) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "Aktuális szoba: %s", manager->rooms[manager->current_room].name);
    render_text(renderer, font, buffer, 50, 50);

    if (manager->current_room == 0) {
        eloszoba_render(renderer, font, &manager->eloszoba, manager->kod_input);
    } else {
        if (!manager->rooms[manager->current_room].puzzle_solved) {
            manager->rooms[manager->current_room].puzzle->render(manager->rooms[manager->current_room].puzzle);
        } else {
            render_text(renderer, font, "Puzzle megoldva!", 50, 100);
        }
    }
}

void scene_manager_update(SceneManager* manager) {
    if (manager->current_room == 0)
    {
       return;   //mivel már az eseménykezelő megoldja a logikát
    }
    
    Puzzle* puzzle = manager->rooms[manager->current_room].puzzle;
    if (!manager->rooms[manager->current_room].puzzle_solved) {
        char input[64];
        printf(">> ");
        scanf("%s", input);

        if (puzzle->solve(puzzle, input)) {
            printf("Puzzle megoldva!\n");
            manager->rooms[manager->current_room].puzzle_solved = true;
        } else {
            printf("Hibás válasz. Próbáld újra!\n");
        }
    }
}

void scene_manager_handle_event(SceneManager* manager, SDL_Event* event) {
    if (manager->current_room == 0) {
        SDL_StartTextInput();
        eloszoba_handle_event(event, &manager->eloszoba, manager->kod_input, &manager->kod_length);

        if (manager->eloszoba.puzzle_solved && !manager->rooms[0].puzzle_solved) {
            manager->rooms[0].puzzle_solved = true;
            printf("Előtér kód megoldva!\n");
        }
    } else {
        // egyéb szobák eseménykezelése, ha kell
    }
}


