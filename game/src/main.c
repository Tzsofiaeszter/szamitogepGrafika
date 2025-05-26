#include "app.h"
#include "input.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    App app = {0};  // kinullázás

    init_app(&app, 800, 600);

    printf("[DEBUG] Main ciklus elott: is_running = %d\n", app.is_running);

    while (app.is_running) {
        printf("[DEBUG] fociklusban vagyunk\n");

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            handle_app_events(&app);
        }

        update_app(&app);
        render_app(&app);
        SDL_Delay(16);
    }

    destroy_app(&app);
    return 0;
}
