// include/puzzle.h
#ifndef PUZZLE_H
#define PUZZLE_H
#include <stdbool.h>

typedef enum {
    PUZZLE_WORD_ORDER,
    //PUZZLE_SCISSOR_PILLOW,
    PUZZLE_CODE_YEAR,
    PUZZLE_LOGIC,
    PUZZLE_CODE_WORD,
} PuzzleType;

typedef enum {
    PUZZLE_STATE_INIT,
    PUZZLE_STATE_ACTIVE,
    PUZZLE_STATE_SOLVED,
} PuzzleState;

typedef struct Puzzle {
    PuzzleType type;
    void* data;
    bool solved;
    PuzzleState state;

    void (*init)(struct Puzzle* puzzle);
    bool (*solve)(struct Puzzle* puzzle, void* input);
    void (*render)(struct Puzzle* puzzle);
} Puzzle;

    // === PUZZLE: WORD_ORDER ===
    typedef struct {
        char correct_word[5];
        int correct_order[4];
    } PuzzleWordOrderData;
/*
      // === PUZZLE: SCISSOR_PILLOW ===
    typedef struct {
        bool has_scissors;
        bool pillow_cut;
    } PuzzleScissorPillowData;
*/

Puzzle* puzzle_create(PuzzleType type);
bool puzzle_try_solve(Puzzle* puzzle, void* data);
void puzzle_render(Puzzle* puzzle);
void puzzle_free(Puzzle* puzzle);

#endif