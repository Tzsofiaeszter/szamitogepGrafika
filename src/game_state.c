#include <stdio.h>
#include"init.h"
#include "game_state.h"

// Jelenlegi állapotfüggvény
static void (*current_state_func)(GameState*) = NULL;

// Enum verzió az aktuális állapotról (pl. UI-hoz, logoláshoz)
static GameStateEnum current_enum_state = GAME_STATE_MENU;

void game_state_init(GameState* state) {
    state->running = true;
    state->show_help = false;
    state->brightness = 255;

    // SDL inicializálásának ellenőrzése
    if (!init_sdl()) {
        fprintf(stderr, "SDL  inicializálás sikertelen.\n");
        state->running = false;  // Ha nem sikerült az inicializálás, leállítjuk a játékot
        return;
    }

    // Kezdő állapot beállítása (Főmenü)
    game_state_set(state_main_menu, GAME_STATE_MENU);
}

void game_state_update(GameState* state) {
    // Ha van beállítva aktuális állapot függvény, végrehajtjuk
    if (current_state_func) {
        current_state_func(state);
    }
}

void game_state_set(void (*new_state)(GameState*), GameStateEnum enum_state) {
    current_state_func = new_state;  // Az új állapotfüggvény beállítása
    current_enum_state = enum_state; // Az aktuális állapot enum értékének beállítása
}

GameStateEnum game_state_get_enum() {
    return current_enum_state;
}

/*// A játék befejezésekor a tisztítást végző függvény
void game_state_cleanup() {
    cleanup_sdl();  // SDL és TTF könyvtárak megfelelő felszabadítása
}
*/
// Állapotfüggvények definíciói

void state_main_menu(GameState* state) {
    printf("\n--- Főmenü ---\n");
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
    }
}

void state_help(GameState* state) {
    printf("\n--- Súgó ---\n");
    printf("Használható billentyűk: WASD a mozgáshoz, ESC a kilépéshez\n");
    printf("b - Vissza a főmenübe\n");

    char input = getchar();  // Választás bekérése
    while (getchar() != '\n');  // Input buffer ürítése

    if (input == 'b') {
        game_state_set(state_main_menu, GAME_STATE_MENU);  // Vissza a főmenübe
    }
}

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

void state_exit(GameState* state) {
    state->running = false;
}
