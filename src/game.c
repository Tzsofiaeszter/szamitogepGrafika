#include "input.h"
#include "game.h"
#include "scene_manager.h"
#include "game_state.h"
#include "app.h" // App objektum inicializálásához/eléréséhez
#include "light.h" // A fényerő beállításához

#include <stdlib.h>
#include <SDL2/SDL.h>

/*
Inicializálja a játékhoz szükséges objektumokat:
 - létrehozza a jelenetkezelőt,
 - inicializálja a bemenetkezelőt,
 - ellenőrzi, hogy sikeres volt-e a jelenetkezelő létrehozása.
*/
void game_init(GameContext* context) {
    // Inicializáljuk a GameContext tagokat
    context->state = (GameState*)malloc(sizeof(GameState));
    context->menu = (Menu*)malloc(sizeof(Menu));
    context->manager = scene_manager_create(); // Feltételezve, hogy ez malloc-ot használ

    if (!context->state || !context->menu || !context->manager) {
        fprintf(stderr, "Hiba: nem sikerült a GameContext tagok inicializálása.\n");
        exit(1);
    }

    game_state_init(context->state); // Inicializáljuk a GameState-et
    menu_init(context->menu); // Inicializáljuk a Menüt
    input_init(context->state, context->menu); // Input kezelő inicializálása

    context->running = true;
    context->brightness = 255; // Alapértelmezett fényerő
    context->show_help = false; // Alapértelmezett súgó állapot
}

/*
A játék frissítése: meghívja a jelenetkezelő frissítőfüggvényét,
ami a jelenlegi aktív jelenetet (pl. menü, játék) frissíti.
*/
void game_update(GameContext* context) {
    scene_manager_update(context->manager);
}

/*
Eseménykezelés:
 - Kilépés (ablak bezárása)
 - Bemenetkezelőnek továbbítja az eseményt
 - Billentyűleütések kezelése:
   - ESC: főmenübe lépés és játék leállítása
   - H: súgó megjelenítésének ki/bekapcsolása
   - - (mínusz): fényesség csökkentése
*/
void game_handle_event(GameContext* context, SDL_Event* event) {
    if (event->type == SDL_QUIT) {
        context->running = false;
        return;
    }

    input_handle_event(event); // Esemény továbbítása az input kezelőnek

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                game_state_set(context->state_main_menu, GAME_STATE_EXIT); // Feltételezzük, hogy context->state_main_menu létezik
                context->running = false;
                break;
            case SDLK_h:
                context->show_help = !context->show_help;
                break;
            case SDLK_MINUS:
                // Fényesség csökkentése
                if (context->brightness > 0) {
                    context->brightness -= 10;
                    glLightf(GL_LIGHT0, GL_AMBIENT, context->brightness / 255.0f); // Példa a fényesség állítására
                }
                break;
            case SDLK_PLUS:
                // Fényesség növelése
                if (context->brightness < 255) {
                    context->brightness += 10;
                    glLightf(GL_LIGHT0, GL_AMBIENT, context->brightness / 255.0f); // Példa a fényesség állítására
                }
                break;
            // További billentyűk kezelése az input.c-ben
            default:
                break;
        }
    }
}

/*
A játék kirajzolása (ha a game.c felelős a fő renderelésért)
*/
void game_render(const GameContext* context) {
    // Itt hívhatjuk meg a scene_manager_render-t
    scene_manager_render(context->manager);

    // Különleges UI elemek kirajzolása, ha vannak
    if (context->show_help) {
        // Rendereld a súgó textúrát/szöveget
        // show_help_text(); // Ez egy függvény lenne, ami a súgóval foglalkozik
    }
}

/*
Felszabadítja a játék által lefoglalt erőforrásokat.
*/
void game_cleanup(GameContext* context) {
    if (context->manager) {
        scene_manager_destroy(context->manager); // Feltételezve, hogy ez felszabadítja
    }
    if (context->state) {
        free(context->state);
    }
    if (context->menu) {
        free(context->menu);
    }
    // SDL_Quit() valószínűleg az App destruktorában van
}

/*
Ellenőrzi, hogy a játék fut-e még.
*/
bool is_game_running(const GameContext* context) {
    return context->running;
}