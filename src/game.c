#include "input.h"
#include "game.h"
#include "scene_manager.h"
#include "game_state.h"

#include <stdlib.h>
#include <SDL2/SDL.h>

// --- Globális változók ---
    static GameState* state = NULL;
    static Menu* menu = NULL;
    static SceneManager* manager = NULL;
    static bool running = true;
    static int brightness = 255;
    static bool show_help = false;


/*
Inicializálja a játékhoz szükséges objektumokat:
 - létrehozza a jelenetkezelőt,
 - inicializálja a bemenetkezelőt,
 - ellenőrzi, hogy sikeres volt-e a jelenetkezelő létrehozása.
*/
    void game_init() {
        manager = scene_manager_create();
        input_init(state, menu);
        if (!manager) exit(1);
    }

/*
A játék frissítése: meghívja a jelenetkezelő frissítőfüggvényét,
ami a jelenlegi aktív jelenetet (pl. menü, játék) frissíti.
*/
    void game_update() {
        scene_manager_update(manager);
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
    void game_handle_event(SDL_Event* event) {
        if (event->type == SDL_QUIT) {
            running = false;
            return;
        }

        input_handle_event(event); 

        if (event->type == SDL_KEYDOWN) {
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    game_state_set(state_main_menu, GAME_STATE_EXIT);
                    running = false;
                    break;
                case SDLK_h:
                    show_help = !show_help;
                    break;
                case SDLK_MINUS:
                case SDLK_KP_MINUS:
                    brightness = (brightness > 10) ? brightness - 10 : 0;
                    break;
            }
        }
    }


/*
Visszaadja, hogy a játék még fut-e.
A fő ciklus ezt használja annak eldöntésére, hogy folytassa-e a működést.
*/
    bool game_is_running() {
        return running;
    }
