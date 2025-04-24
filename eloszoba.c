#include "scene_manager.h"
#include "puzzle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Puzzle* code_puzzle = NULL;

void eloszoba_init(SceneManager* manager) {
    code_puzzle = puzzle_create(PUZZLE_CODE_YEAR);
}

void eloszoba_render(SceneManager* manager) {
    printf("=== Előszoba ===\n");
    printf("Egy zárt ajtóval szembesülsz. Van egy számkódos panel.\n");

    if (!code_puzzle->solved) {
        puzzle_render(code_puzzle);
    } else {
        printf("A zár kinyílt! Az ajtó nyitva van.\n");
    }
}

void eloszoba_handle_input(SceneManager* manager, const char* input) {
    if (!code_puzzle->solved) {
        if (puzzle_try_solve(code_puzzle, (void*)input)) {
            printf("Helyes kód! Az ajtó kinyílt.\n");
            // Pl. szoba váltás:
            // scene_manager_go_to(manager, SCENE_NAPPALI);
        } else {
            printf("Hibás kód. Próbáld újra!\n");
        }
    } else {
        printf("Az ajtó már nyitva van.\n");
    }
}

void eloszoba_cleanup(SceneManager* manager) {
    puzzle_free(code_puzzle);
}
