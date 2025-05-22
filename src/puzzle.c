#include "puzzle.h"
//#include "game_state.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Inicializálja a szókirakó puzzle-t: helyes szó és helyes betűsorrend beállítása
    static void word_order_init(Puzzle* puzzle) {
        PuzzleWordOrderData* data = malloc(sizeof(PuzzleWordOrderData));
        strcpy(data->correct_word, "HOLD");
        int order[4] = {4, 1, 2, 3};
        memcpy(data->correct_order, order, sizeof(order));
        puzzle->data = data;
        puzzle->state = PUZZLE_STATE_ACTIVE;
    }

// Ellenőrzi, hogy a játékos helyesen adta-e meg a betűk sorrendjét
    static bool word_order_solve(Puzzle* puzzle, void* input) {
        if (!puzzle || !input || puzzle->state != PUZZLE_STATE_ACTIVE) return false;

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

// Kirajzolja a szókirakó feladvány szöveges leírását a képernyőre
    static void word_order_render(Puzzle* puzzle) {
        if (!puzzle) return;
        PuzzleWordOrderData* data = (PuzzleWordOrderData*)puzzle->data;
         if (data) {
        printf("[Szókirakó] Rendezd a betűket helyes sorrendbe!\n");
        printf("Betűk: H - O - L - D\n");
        printf("Pl.: Írd be a sorrendet számként (pl.: 4 1 2 3)\n");
        (void)puzzle; // Jelzi a fordítónak, hogy a paraméter szándékosan nincs használva
    }
}

   /*
  
    static void scissor_pillow_init(Puzzle* puzzle) {
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

    // Inicializálja a kódos puzzle-t (aktuális év megadása szükséges)
    static void code_year_init(Puzzle* puzzle) {
    if (puzzle) {
        PuzzleCodeYearData* data = malloc(sizeof(PuzzleCodeYearData));
        if (data) {
            strcpy(data->correct_code, "2025");
            puzzle->data = data;
            puzzle->state = PUZZLE_STATE_ACTIVE;
        } else {
            fprintf(stderr, "Hiba: nem sikerült memóriát foglalni a CodeYearData-nak.\n");
            puzzle->state = PUZZLE_STATE_ERROR;
        }
    }
}

// Ellenőrzi, hogy a játékos helyesen adta-e meg az évet (2025)
    static bool code_year_solve(Puzzle* puzzle, void* input) {
    if (!puzzle || !input || puzzle->state != PUZZLE_STATE_ACTIVE) return false;

    char* user_code = (char*)input;
    PuzzleCodeYearData* data = (PuzzleCodeYearData*)puzzle->data;

    if (strcmp(user_code, data->correct_code) == 0) {
        puzzle->solved = true;
        puzzle->state = PUZZLE_STATE_SOLVED;
        return true;
    }
    return false;
}

// Kirajzolja a záras puzzle szöveges leírását a képernyőre
    static void code_year_render(Puzzle* puzzle) {
        printf("[Kódzár] Az ajtó zárva van. Írd be a 4 jegyű kódot (aktuális év):\n");
        (void)puzzle; // Jelzi a fordítónak, hogy a paraméter szándékosan nincs használva
    }

// Inicializál egy üres (placeholder) logikai puzzle-t – alapértelmezett viselkedés
    static void logic_init(Puzzle* puzzle) {
    if (puzzle) {
        puzzle->data = NULL;                        // Nincs specifikus adat
        puzzle->state = PUZZLE_STATE_ACTIVE;
    }
}

// Automatikusan megoldja a logikai puzzle-t (helyettesítő logika)
    static bool logic_solve(Puzzle* puzzle, void* input) {
        if (!puzzle || puzzle->state != PUZZLE_STATE_ACTIVE) return false;

        puzzle->solved = true;
        puzzle->state = PUZZLE_STATE_SOLVED;
        return true;
    }

// Kirajzolja az üres logikai puzzle üzenetét
    static void logic_render(Puzzle* puzzle) {
        if (!puzzle) return;
        //printf("[Logikai Puzzle] \n");
        puzzle; // Jelzi a fordítónak, hogy a paraméter szándékosan nincs használva
    }

// Létrehoz egy új puzzle-típust a megadott típus alapján, és inicializálja azt
    Puzzle* puzzle_create(PuzzleType type) {
        Puzzle* puzzle = malloc(sizeof(Puzzle));
        if (!puzzle) {
            fprintf(stderr, "Hiba: nem sikerült memóriát foglalni a Puzzle számára!\n");
            return NULL;
        }

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

// Megpróbálja megoldani a puzzle-t, ha még nincs megoldva
    bool puzzle_try_solve(Puzzle* puzzle, void* data) {
        if (!puzzle || !puzzle->solve || puzzle->solved)
            return false;
        return puzzle->solve(puzzle, data);
    }

// Megjeleníti a puzzle aktuális állapotát, és meghívja a hozzá tartozó render függvényt
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

// Felszabadítja a puzzle memóriaterületét
    void puzzle_destroy(Puzzle* puzzle) {
        if (puzzle) {
            if (puzzle->data){
                free(puzzle->data);
            puzzle->data = NULL;
        }
          free(puzzle);
    }
}

