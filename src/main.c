#include <stdio.h>
#include <SDL2/SDL.h> 

#include "app.h"

int main(int argc, char* argv[]) {
    App app;
    SDL_Event event; 

    init_app(&app, 800, 600);
    while (app.is_running) {
        while (SDL_PollEvent(&event)) { 
             handle_app_events(&app, &event);
            switch (event.type) {
                case SDL_QUIT:
                    app.is_running = false;
                    break;
            }
        }
        update_app(&app);
        render_app(&app);
        SDL_Delay(16); 
    }
    destroy_app(&app);

    return 0;
}

/*
FUTTATÁS
cd C:\Users\Turi Zsófia\Documents\Grafika\szamitogepGrafika\szamitogepGrafika-1\szamitogepGrafika\feladat\Hadesz
make --debug=b
*/