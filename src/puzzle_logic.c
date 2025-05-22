#include "puzzle_logic.h"
#include "game_state.h"
#include "puzzle.h"          // Szükséges: puzzle_create, puzzle_free, puzzle_try_solve
#include "eloszoba.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

// Inicializál egy puzzle szobát azonosítóval és típusával
void puzzle_room_init(PuzzleRoom* room, RoomID id, PuzzleType type) {
    if (room) {
        room->room_id = id;
        room->puzzle = puzzle_create(type);
        room->puzzle_solved = false;
    }
}

// Frissíti a puzzle szoba állapotát
void puzzle_room_update(PuzzleRoom* room, GameState* state) {
    if (!room || !state) return;

    if (room->puzzle->state == PUZZLE_STATE_SOLVED && !state->solved_rooms[room->room_id]) {
        room->puzzle_solved = true;
        state->solved_rooms[room->room_id] = true;
        state->doors[room->room_id].is_open = true;

        if (room->room_id == ELOSZOBA) {
            state->accessible_rooms[NAPPALI] = true;
            printf("Az eloszoba ajtaja kinyílt. A nappali elérhetővé vált.\n");
        }
    }
}

// Kirajzolja a puzzle szobát
void puzzle_room_render(PuzzleRoom* room, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &(SDL_Rect){100, 100, 600, 400});

    if (room->puzzle && room->puzzle->state == PUZZLE_STATE_SOLVED) {
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

// Kezeli a felhasználói bemenetet a puzzle szobában
void puzzle_room_handle_input(PuzzleRoom* room, GameState* state, const SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_RETURN:
                if (room->puzzle && room->puzzle->state == PUZZLE_STATE_ACTIVE) {
                    char answer[64];
                    printf("Add meg a megfejtést: ");
                    scanf("%63s", answer);

                    if (puzzle_try_solve(room->puzzle, answer)) {
                        printf("Helyes megfejtés!\n");
                    } else {
                        printf("Nem jó a megfejtés.\n");
                    }
                } else if (room->puzzle && room->puzzle->state == PUZZLE_STATE_SOLVED) {
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

// Felszabadítja a puzzle szoba által lefoglalt erőforrásokat
void puzzle_room_destroy(PuzzleRoom* room) {
    puzzle_destroy(room->puzzle);
}
