#include "render.h"
#include "menu.h"
#include "game_state.h"
#include "app.h"

#include <SDL2/SDL.h>
#include <GL/gl.h>          //  OpenGL-t rendereléshez


// Közös háttér kirajzolás fényerő figyelembevételével
void render_common_background(SDL_Renderer* renderer, int width, int height, int brightness) {
    (void)width;
    (void)height;    
    
    if (renderer) {
        SDL_SetRenderDrawColor(renderer, (Uint8)brightness, (Uint8)brightness, (Uint8)brightness, 255);
        SDL_RenderClear(renderer);
        }
}


// Menü kirajzolása
// A függvény szignatúrája megegyezik a render.h-ban deklarálttal
void render_menu(SDL_Renderer* renderer, const Menu* menu, const GameState* game_state, const App* app) {
    if (!renderer || !menu || !game_state || !app) return;

    // A render_common_background függvénynek most az App struktúrából adjuk át a szélességet és magasságot
    render_common_background(renderer, app->window_width, app->window_height, app->game_state.brightness);

    // Itt rajzolhatod ki a menü grafikus elemeit, textúrákat stb.
    // Ha nem használsz TTF-et, akkor a szöveget más módon kell megjeleníteni,
    // például előre renderelt textúrákkal vagy primitív grafikai elemekkel.
}

// Súgó képernyő kirajzolása
// A függvény szignatúrája megegyezik a render.h-ban deklarálttal
void render_help(SDL_Renderer* renderer, const GameState* game_state, const App* app) {
    if (!renderer || !game_state || !app) return;

    render_common_background(renderer, app->window_width, app->window_height, app->game_state.brightness);

    // Itt rajzolhatod ki a súgó grafikus elemeit, textúrákat stb.
    // Hasonlóan a menühöz, ha nincs TTF, akkor más módon kell a szöveget/képeket kirajzolni.
}