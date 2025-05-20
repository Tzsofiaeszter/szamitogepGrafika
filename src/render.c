#include "render.h"
#include <stdio.h>
#include <SDL2/SDL.h>


Camera camera = {0, 0, 1.0f};
int brightness = 128; // alap fényerő


// Közös háttér kirajzolás fényerő figyelembevételével
void render_common_background(SDL_Renderer* renderer, int width, int height) {
    SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, 255);
    SDL_RenderClear(renderer);
}
