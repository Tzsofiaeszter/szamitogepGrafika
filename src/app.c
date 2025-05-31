#include "app.h"
#include "scene.h"
#include "camera.h"

#include <stdio.h>
#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height){
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Game!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->selected_chair = 1; // Alapértelmezetten szék1 aktív

    app->is_running = true;
}

void init_opengl(){
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glDisable(GL_CULL_FACE);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height){
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -0.08, 0.08,
        -0.06, 0.06,
        0.1, 100
    );
}

// Ez a függvény kezeli az aktív szék mozgását a nyilakkal
void handle_keyboard_input(App* app, const SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        SDL_Keycode key = event->key.keysym.sym;

        switch (key) {
            case SDLK_1:
                app->selected_chair = 1;
                break;
            case SDLK_2:
                app->selected_chair = 2;
                break;

            // Nyilak mozgatják az aktuálisan kiválasztott széket
            case SDLK_UP:
                if (app->selected_chair == 1)
                    move_szek1(&(app->scene), 0.0f, 0.1f, 0.0f);
                else if (app->selected_chair == 2)
                    move_szek2(&(app->scene), 0.0f, 0.1f, 0.0f);
                break;

            case SDLK_DOWN:
                if (app->selected_chair == 1)
                    move_szek1(&(app->scene), 0.0f, -0.1f, 0.0f);
                else if (app->selected_chair == 2)
                    move_szek2(&(app->scene), 0.0f, -0.1f, 0.0f);
                break;

            case SDLK_LEFT:
                if (app->selected_chair == 1)
                    move_szek1(&(app->scene), -0.1f, 0.0f, 0.0f);
                else if (app->selected_chair == 2)
                    move_szek2(&(app->scene), -0.1f, 0.0f, 0.0f);
                break;

            case SDLK_RIGHT:
                if (app->selected_chair == 1)
                    move_szek1(&(app->scene), 0.1f, 0.0f, 0.0f);
                else if (app->selected_chair == 2)
                    move_szek2(&(app->scene), 0.1f, 0.0f, 0.0f);
                break;

            case SDLK_PAGEUP:
                if (app->selected_chair == 1)
                    move_szek1(&(app->scene), 0.0f, 0.0f, 0.1f);
                else if (app->selected_chair == 2)
                    move_szek2(&(app->scene), 0.0f, 0.0f, 0.1f);
                break;

            case SDLK_PAGEDOWN:
                if (app->selected_chair == 1)
                    move_szek1(&(app->scene), 0.0f, 0.0f, -0.1f);
                else if (app->selected_chair == 2)
                    move_szek2(&(app->scene), 0.0f, 0.0f, -0.1f);
                break;

            default:
                break;
        }
    }
}


void handle_app_events(App* app){
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x, y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_KEYDOWN:
            // Először kezeljük az aktív szék mozgását a nyilakkal
            handle_keyboard_input(app, &event);

            // Egyéb billentyűk kezelése
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_L:
                app->scene.lighting_enabled = !app->scene.lighting_enabled;
                //if (app->scene.lighting_enabled) {
                 //   glEnable(GL_LIGHTING);
                //} else {
                   // glDisable(GL_LIGHTING);
                //}
                break;
            case SDL_SCANCODE_H:
                app->scene.show_help_visible = !app->scene.show_help_visible;
                break;
            case SDL_SCANCODE_C:
                increase_light(&app->scene);
                break;
            case SDL_SCANCODE_N:
                decrease_light(&app->scene);
                break;

            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;

        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;

        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;

        case SDL_QUIT:
            app->is_running = false;
            break;

        default:
            break;
        }
    }
}

void update_app(App* app){
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));
}

void render_app(App* app){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // Világítás állapotának megerősítése minden render előtt
    if (app->scene.lighting_enabled) {
        glEnable(GL_LIGHTING);
    } else {
        glDisable(GL_LIGHTING);
    }

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->camera.is_preview_visible) {
        show_texture_preview();
    }

    if (app->scene.show_help_visible) {
        render_help_overlay(&(app->scene));
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app){
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
        app->gl_context = NULL;
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
        app->window = NULL;
    }

    IMG_Quit();
    SDL_Quit();
}
