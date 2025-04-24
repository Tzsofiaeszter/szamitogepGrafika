#include <stdio.h>
#include "render.h"
#include "displayHelp.h"
#include "game.h"

void render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) { // Egy adott szöveg kiírását végzi a megadott (x, y) koordinátára a képernyőre.
    SDL_Color color = {255, 255, 255, 255};                                                // Fehér színt állítunk be a szöveghez (RGBA - 255,255,255 fehér, 255 alfa: teljesen átlátszatlan).
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);                      // Egy ideiglenes felületre kiírjuk a szöveget a megadott betűtípussal és színnel.
    if (!surface) {                                                                        // Ha nem sikerült létrehozni a felületet...
        SDL_Log("Text surface hiba: %s", TTF_GetError());                                  // akkor kiírunk egy hibát az SDL logba.
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);                 // Létrehozunk egy textúrát a felületből, amelyet már a GPU tud megjeleníteni.
    if (!texture) {                                                                         // Ha a textúra létrehozása is hibás
        SDL_Log("Text texture hiba: %s", SDL_GetError());                                   // akkor kiírunk egy hibát az SDL logba.
        SDL_FreeSurface(surface);                                                           // Felszabadítjuk a felületet
        return;
    }

    SDL_Rect dst = {x, y, surface->w, surface->h};                                 // Megadjuk a cél pozíciót és méretet (x, y, szélesség, magasság), ahová a szöveget szeretnénk kirajzolni.
    SDL_RenderCopy(renderer, texture, NULL, &dst);                                 // A textúrát átmásoljuk a képernyőre (vagy pontosabban az SDL renderelő bufferébe).

    SDL_FreeSurface(surface);                                                      // A felületet már nem használjuk, törölhetjük.
    SDL_DestroyTexture(texture);                                                   // A textúrát is felszabadítjuk.
}

void render_help_overlay(SDL_Renderer* renderer, TTF_Font* font, int window_width, int window_height, bool show) {  // Ez a függvény megjeleníti a súgó overlay-t, ha a show értéke true.
    if (!show) return;                                                                                              // Ha a súgó nem aktív, akkor kilépünk a függvényből.

    // Háttér overlay (átlátszó fekete)
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);                                                      // Beállítjuk az átlátszóság támogatását a rajzoláshoz.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);                                                                 // Fekete színt állítunk be, 180-as alfával (félig átlátszó háttér).
    SDL_Rect background = {window_width / 4, window_height / 4, window_width / 2, window_height / 2};               // Létrehozunk egy téglalapot a képernyő közepére, ez lesz a háttér overlay.
    
    SDL_RenderFillRect(renderer, &background);                                                                      // Kirajzoljuk az overlay hátterét.

    // Szövegek // A szövegek kiindulási (x, y) pozícióját határozzuk meg a háttéren belül.
    int x = window_width / 4 + 20;
    int y = window_height / 4 + 20;

    render_text(renderer, font, "Használati útmutató:", x, y); y += 40;                 // Címsor kiírása, majd eltoljuk a következő sor pozícióját lejjebb.
    render_text(renderer, font, "W/A/S/D - Mozgás / Kamera", x, y); y += 30;            // Mozgásvezérlés leírása.
    render_text(renderer, font, "+ / -     - Fényerő állítása", x, y); y += 30;         // Fényerő szabályozás.
    render_text(renderer, font, "O         - Belépés a nappaliba", x, y); y += 30;      // Belépés egy szobába, ha feltétel teljesül.
    render_text(renderer, font, "H         - Súgó be/ki", x, y); y += 30;               // A súgó ki-/bekapcsolás vezérlése.
    render_text(renderer, font, "ESC       - Kilépés", x, y);                           // Kilépési utasítás.
}

void input_handle(SDL_Event* event) {             //globális változó, tehát a fényessgéegt így tudjuk meghívni hozzá
    if (event->key.keysym.sym == SDLK_PLUS) {
        if (brightness < 255) brightness += 10;
    }
}