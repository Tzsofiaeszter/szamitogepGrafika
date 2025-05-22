#include "app.h"
#include "input.h"

#include <stdio.h>
#include <SDL2/SDL.h> 

int main(int argc, char* argv[]) {
    App app;
    SDL_Event event;
    init_app(&app, 800, 600);
  
    InputContext input_context;
    input_init(&input_context, &app.game_state, &app.menu, &app.camera, &app);

    while (app.game_state.running) {
        while (SDL_PollEvent(&event)) { 
            input_handle_event(&input_context, &event);
            }
        
    // Alkalmazás logikájának frissítése
        update_app(&app);
    // Alkalmazás kirajzolása
        render_app(&app);

        game_state_update_current(&app.game_state);

        SDL_GL_SwapWindow(app.window);     // Buffer csere, képernyő frissítése
        SDL_Delay(16); 
    }
    destroy_app(&app);

    return 0;
}

/*
FUTTATÁS
cd C:\Users\Turi Zsófia\Documents\Grafika\szamitogepGrafika\szamitogepGrafika-1\szamitogepGrafika\feladat\Hadesz
make 
game
*/