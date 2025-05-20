// src/puzzle.c
#include "puzzle.h"
#include "game_state.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// === PUZZLE: WORD_ORDER ===
typedef struct {
    char correct_word[5];
    int correct_order[4];
} PuzzleWordOrderData;

static void word_order_init(Puzzle* puzzle) {
    PuzzleWordOrderData* data = malloc(sizeof(PuzzleWordOrderData));
    strcpy(data->correct_word, "HOLD");
    int order[4] = {4, 1, 2, 3};
    memcpy(data->correct_order, order, sizeof(order));
    puzzle->data = data;
    puzzle->state = PUZZLE_STATE_ACTIVE;
}

static bool word_order_solve(Puzzle* puzzle, void* input) {
    int* user_order = (int*)input;
    PuzzleWordOrderData* data = (PuzzleWordOrderData*)puzzle->data;
    for (int i = 0; i < 4; ++i) {
        if (user_order[i] != data->correct_order[i])
            return false;
    }
    puzzle->solved = true;
    puzzle->state = PUZZLE_STATE_SOLVED;
    return true;
}

static void word_order_render(Puzzle* puzzle) {
    printf("[Szókirakó] Rendezd a betűket helyes sorrendbe!\n");
    printf("Betűk: H - O - L - D\n");
    printf("Pl.: Írd be a sorrendet számként (pl.: 4 1 2 3)\n");
    (void)puzzle; // Jelzi a fordítónak, hogy a paraméter szándékosan nincs használva
}

// === PUZZLE: SCISSOR_PILLOW ===
typedef struct {
    bool has_scissors;
    bool pillow_cut;
} PuzzleScissorPillowData;

/*static void scissor_pillow_init(Puzzle* puzzle) {
    PuzzleScissorPillowData* data = malloc(sizeof(PuzzleScissorPillowData));
    data->has_scissors = false;
    data->pillow_cut = false;
    puzzle->data = data;
    puzzle->state = PUZZLE_STATE_ACTIVE;
}

static bool scissor_pillow_solve(Puzzle* puzzle, void* input) {
    PuzzleScissorPillowData* data = (PuzzleScissorPillowData*)puzzle->data;
    const char* action = (const char*)input;

    if (strcmp(action, "take_scissors") == 0) {
        data->has_scissors = true;
        printf("→ Felvetted az ollót.\n");
        return false;
    } else if (strcmp(action, "cut_pillow") == 0) {
        if (!data->has_scissors) {
            printf("→ Nincs nálad olló!\n");
            return false;
        }
        if (data->pillow_cut) {
            printf("→ A párna már fel van vágva.\n");
            return false;
        }

        data->pillow_cut = true;
        puzzle->solved = true;
        puzzle->state = PUZZLE_STATE_SOLVED;
        printf("→ Felvágtad a párnát, és találtál benne egy kulcsot!\n");
        return true;
    }

    printf("→ Ismeretlen parancs.\n");
    return false;
}

static void scissor_pillow_render(Puzzle* puzzle) {
    PuzzleScissorPillowData* data = (PuzzleScissorPillowData*)puzzle->data;
    printf("[Párna Puzzle] A szobában van egy rózsaszín párna és egy polc.\n");

    if (!data->has_scissors) {
        printf("A polcon egy ollót látsz.\n");
    } else {
        printf("Az olló nálad van.\n");
    }

    if (data->pillow_cut) {
        printf("A párna fel van vágva, és egy kulcs hever mellette.\n");
    } else {
        printf("A párna ép. Talán elrejt valamit?\n");
    }

    printf("Parancsok: take_scissors / cut_pillow\n");
    (void)puzzle; // Jelzi a fordítónak, hogy a paraméter szándékosan nincs használva
}
*/
// === PUZZLE: CODE_YEAR ===
static void code_year_init(Puzzle* puzzle) {
    puzzle->data = NULL;
    puzzle->state = PUZZLE_STATE_ACTIVE;
}

static bool code_year_solve(Puzzle* puzzle, void* input) {
    const char* guess = (const char*)input;
    if (strcmp(guess, "2025") == 0) {
        puzzle->solved = true;
        puzzle->state = PUZZLE_STATE_SOLVED;
        return true;
    }
    return false;
}

static void code_year_render(Puzzle* puzzle) {
    printf("[Kódzár] Az ajtó zárva van. Írd be a 4 jegyű kódot (aktuális év):\n");
    (void)puzzle; // Jelzi a fordítónak, hogy a paraméter szándékosan nincs használva
}

// === PUZZLE: LOGIC (üres placeholder) ===
static void logic_init(Puzzle* puzzle) {
    puzzle->data = NULL;
    puzzle->state = PUZZLE_STATE_ACTIVE;
}

static bool logic_solve(Puzzle* puzzle, void* input) {
    puzzle->solved = true;
    puzzle->state = PUZZLE_STATE_SOLVED;
    (void)input; // Jelzi a fordítónak, hogy a paraméter szándékosan nincs használva
    return true;
}

static void logic_render(Puzzle* puzzle) {
    printf("[Logikai Puzzle] \n");
    (void)puzzle; // Jelzi a fordítónak, hogy a paraméter szándékosan nincs használva
}

// === Puzzle Factory ===
Puzzle* puzzle_create(PuzzleType type) {
    Puzzle* puzzle = malloc(sizeof(Puzzle));
    puzzle->type = type;
    puzzle->data = NULL;
    puzzle->solved = false;
    puzzle->state = PUZZLE_STATE_INIT;

    switch (type) {
        case PUZZLE_WORD_ORDER:
            puzzle->init = word_order_init;
            puzzle->solve = word_order_solve;
            puzzle->render = word_order_render;
            break;
       /* case PUZZLE_SCISSOR_PILLOW:
            puzzle->init = scissor_pillow_init;
            puzzle->solve = scissor_pillow_solve;
            puzzle->render = scissor_pillow_render;
            break;*/
        case PUZZLE_CODE_YEAR:
            puzzle->init = code_year_init;
            puzzle->solve = code_year_solve;
            puzzle->render = code_year_render;
            break;
        case PUZZLE_LOGIC:
        default:
            puzzle->init = logic_init;
            puzzle->solve = logic_solve;
            puzzle->render = logic_render;
            break;
    }

    if (puzzle->init)
        puzzle->init(puzzle);

    return puzzle;
}

bool puzzle_try_solve(Puzzle* puzzle, void* data) {
    if (!puzzle || !puzzle->solve || puzzle->solved)
        return false;
    return puzzle->solve(puzzle, data);
}

void puzzle_render(Puzzle* puzzle) {
    if (!puzzle) return;

    printf("\n=== Puzzle állapot: ");
    switch (puzzle->state) {
        case PUZZLE_STATE_INIT:   printf("INIT"); break;
        case PUZZLE_STATE_ACTIVE: printf("AKTÍV"); break;
        case PUZZLE_STATE_SOLVED: printf("MEGOLDVA"); break;
    }
    printf(" ===\n");

    if (puzzle->render)
        puzzle->render(puzzle);
}

void puzzle_free(Puzzle* puzzle) {
    if (puzzle) {
        if (puzzle->data)
            free(puzzle->data);
        free(puzzle);
    }
}

