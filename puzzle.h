#ifndef PUZZLE_H
#define PUZZLE_H

#include <stdbool.h>

typedef enum {
    PUZZLE_WORD_ORDER,
    PUZZLE_LOGIC,
    PUZZLE_SCISSOR_PILLOW,
    PUZZLE_CODE_YEAR // új típus
} PuzzleType;

typedef struct Puzzle {
    PuzzleType type;
    void* data;
    bool solved;

    void (*init)(struct Puzzle*);
    bool (*solve)(struct Puzzle*, void* input);
    void (*render)(struct Puzzle*);
} Puzzle;

Puzzle* puzzle_create(PuzzleType type);
bool puzzle_try_solve(Puzzle* puzzle, void* data);
void puzzle_render(Puzzle* puzzle);
void puzzle_free(Puzzle* puzzle);

#endif
