/*
#include <stdio.h>
#include<SDL2/SDL.h>
#include "nappali.h"
#include "puzzle_logic.h"
#include "game_state.h"
#include "scene_manager.h"


static PuzzleRoom nappali_room;

void nappali_init(SceneManager* manager) {
    puzzle_room_init(&nappali_room, NAPPALI, PUZZLE_CODE_WORD);
}

void nappali_render(SceneManager* manager) {
    printf("=== Nappali ===\n");
    printf("Ez a nappali.\n");
    printf("A szoba közepén szép színes szőnyeg. Ezen egy kis dohányzóasztal áll, rajta egy tulipánnal teli váza.\n");
    printf("Balra egy sarok ülőgarnitúra, rajta három szép színes párna.\n");
    printf("Jobbra egy nagy polcozott szekrény, rajta televízió, vázák, fényképek, könyvek és egy olló.\n");
    printf("Az ablakon átlátszó függöny van, mögötte rács.\n\n");

    if (!nappali_room.puzzle->solved) {
        printf("Az ajtón egy találós kérdés olvasható:\n");
        printf("\"Mikor fekszel, ő akkor kél.\n");
        printf("Egyszer egész, máskor csak fél.\n");
        printf("Nincsen tüze, mégis lámpás,\n");
        printf("A vándornak szinte áldás.\"\n");
        printf("A megfejtés egy négybetűs szó, betűi össze vannak keverve.\n");
        puzzle_render(nappali_room.puzzle);
    } else {
        printf("A találós kérdést megfejtetted, az ajtó kinyílt.\n");
    }
}

void nappali_handle_input(SceneManager* manager, const char* input) {
    if (!nappali_room.puzzle->solved) {
        if (puzzle_try_solve(nappali_room.puzzle, (void*)input)) {
            printf("Helyes megfejtés! Az ajtó kinyílt.\n");
        } else {
            printf("Nem jó a megfejtés. Próbáld újra!\n");
        }
    } else {
        printf("Az ajtó már nyitva van.\n");
    }
}

void nappali_cleanup(SceneManager* manager) {
    puzzle_room_cleanup(&nappali_room);
}
*/