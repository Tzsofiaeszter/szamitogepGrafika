#include"init.h"
#include "game_state.h"
#include"menu.h"
#include"eloszoba.h"

#include <stdio.h>
#include <string.h> // memset, strcmp miatt


/*
Inicializálja a játék állapotát.
Beállítja az alapértelmezett értékeket és elindítja az SDL-t.
Ha az SDL inicializálása sikertelen, leállítja a játékot.
Alapértelmezett állapotként a főmenüt állítja be.
*/
    void game_state_init(GameState* state) {
        state->running = true;
        state->show_help = false;
        state->brightness = 255;

        state->current_state_func = NULL;               // Kezdetben nincs állapotfüggvény
        state->current_enum_state = GAME_STATE_MENU;    // Kezdő állapot beállítása

        // SDL inicializálásának ellenőrzése
        if (!init_sdl()) {
            fprintf(stderr, "SDL  inicializálás sikertelen.\n");
            state->running = false;  // Ha nem sikerült az inicializálás, leállítjuk a játékot
            return;
        }

        eloszoba_init(&(state->eloszoba_data));
        // Kezdő állapot beállítása (Főmenü)
        game_state_set(state_main_menu, GAME_STATE_MENU);
    }

/*
Meghívja az aktuális állapothoz tartozó függvényt, ha van.
Ez végzi el a fő programlogikát minden ciklusban.
*/

void game_state_update(GameState* state) {
        // Ha van beállítva aktuális állapot függvény, végrehajtjuk
        if (state->current_state_func) {
            state->current_state_func(state);
        }
    }

/*
Visszaadja az aktuális állapot enum értékét.
Hasznos lehet pl. naplózáshoz vagy a felhasználói felület frissítéséhez.
*/
   void game_state_set(GameState* state_obj, GameStateEnum new_state_enum) {
    state_obj->current_enum_state = new_state_enum;

    switch (new_state_enum) {
        case GAME_STATE_MENU:
            state_obj->current_state_func = state_main_menu;
            break;
        case GAME_STATE_PLAYING:
            state_obj->current_state_func = state_play;
            break;
        case GAME_STATE_PAUSED:
            // TODO: state_paused függvény
            state_obj->current_state_func = NULL; 
            break;
        case GAME_STATE_EXIT:
            state_obj->running = false;
            state_obj->current_state_func = NULL;
            break;
        case GAME_STATE_ELOSZOBA:
            state_obj->current_state_func = state_eloszoba;
            break;
        default:
            state_obj->current_state_func = NULL; // Alapértelmezett, ha nincs kezelő
            break;
    }
}

   
/*
A főmenü állapotot megvalósító függvény.
Kiírja a menüpontokat, és kezeli a felhasználói bemenetet.
*/
    void state_main_menu(GameState* state) {
        /*printf("\n--- Főmenü ---\n");
        printf("p - Játék indítása\n");
        printf("h - Súgó\n");
        printf("q - Kilépés\n");
        printf("Választás: ");

        char input = getchar();  // Választás bekérése
        while (getchar() != '\n');  // Input buffer ürítése

        switch (input) {
            case 'p':
                game_state_set(state_play, GAME_STATE_PLAY);  // Játék indítása
                break;
            case 'h':
                game_state_set(state_help, GAME_STATE_HELP);  // Súgó megjelenítése
                break;
            case 'q':
                state->running = false;  // Kilépés a játékból
                break;
            default:
                printf("Érvénytelen választás.\n");  // Hibás input esetén
                break;
        }*/
    }

/*
A súgó állapotot megvalósító függvény.
Kiírja a vezérlési információkat, majd visszatér a főmenübe.
*/
    void state_help(GameState* state) {
        (void)state;
        printf("\n--- Súgó ---\n");
        printf("Használható billentyűk: WASD a mozgáshoz, ESC a kilépéshez\n");
        printf("b - Vissza a főmenübe\n");

        char input = getchar();  // Választás bekérése
        while (getchar() != '\n');  // Input buffer ürítése

        if (input == 'b') {
            game_state_set(state_main_menu, GAME_STATE_MENU);  // Vissza a főmenübe
        }
    }

/*
A játék fő logikáját kezelő állapotfüggvény.
Kiírja a játék lehetőségeit, pl. súgó ki-/bekapcsolása vagy visszatérés a menübe.
*/
    void state_play(GameState* state) {
        printf("\n--- Játék ---\n");
        printf("m - Vissza a főmenübe\n");
        printf("h - Súgó mutatása: %s\n", state->show_help ? "Be" : "Ki");
        printf("Választás: ");

        char input = getchar();     // Választás bekérése
        while (getchar() != '\n');  // Input buffer ürítése

        switch (input) {
            case 'm':
                game_state_set(state_main_menu, GAME_STATE_MENU);  // Vissza a főmenübe
                break;
            case 'h':
                state->show_help = !state->show_help;  // Súgó állapotának váltása
                break;
            default:
                printf("Játékban nem ismert input.\n");  // Hibás input esetén
                break;
        }
    }

/*
A játék leállítását végző állapotfüggvény.
Beállítja, hogy a fő ciklus befejeződjön.
*/
    void state_exit(GameState* state) {
        state->running = false;
    }
