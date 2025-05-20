#include "puzzle_logic.h"
#include"game_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>  

void puzzle_room_init(PuzzleRoom* room, RoomID id, PuzzleType type) {
    room->room_id = id;
    room->puzzle = puzzle_create(type);
}

void puzzle_room_update(PuzzleRoom* room, PuzzleGameState* state) {
    if (room->puzzle->state == PUZZLE_STATE_SOLVED && !state->solved_rooms[room->room_id]) {
        state->solved_rooms[room->room_id] = true;
        state->doors[room->room_id].is_open = true;

        if (room->room_id == ELLOSZOBA) {
            //state->accessible_rooms[NAPPALI] = true;
            printf("Az eloszoba ajtaja kinyilt. A nappali elerhetove valt.\n");
        }
    }
}

void puzzle_room_render(PuzzleRoom* room, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &(SDL_Rect){100, 100, 600, 400});

    if (room->puzzle->state == PUZZLE_STATE_SOLVED) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(1.0f, 1.5f, 0.0f);
            glVertex3f(1.2f, 1.5f, 0.0f);
            glVertex3f(1.2f, 1.7f, 0.0f);
            glVertex3f(1.0f, 1.7f, 0.0f);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
    } else {
        puzzle_render(room->puzzle);
    }
}

void puzzle_room_handle_input(PuzzleRoom* room, PuzzleGameState* state, const SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_RETURN:
                if (room->puzzle->state == PUZZLE_STATE_ACTIVE) {
                    char answer[64];
                    printf("Add meg a megfejtést: ");
                    scanf("%63s", answer);                              // Szövegbevitel a terminálból

                    if (puzzle_try_solve(room->puzzle, answer)) {
                        printf(" Helyes megfejtés!\n");
                    } else {
                        printf("Nem jó a megfejtés.\n");
                    }
                } else if (room->puzzle->state == PUZZLE_STATE_SOLVED) {
                    printf("Ez a puzzle már meg van oldva.\n");
                }
                break;
            case SDLK_ESCAPE:
                state->exit_game = true;
                break;
            default:
                break;
        }
    }
}

void puzzle_room_cleanup(PuzzleRoom* room) {
    puzzle_free(room->puzzle);
}
