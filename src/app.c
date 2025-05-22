#include "app.h"
#include "scene.h"
#include "light.h"      // A fényekhez
#include "input.h"      // InputContext és input_handle_event hívásához
#include "game_state.h" // GameState inicializálásához
#include "menu.h"       // Menu inicializálásához
#include "init.h"       // init_opengl, reshape, init_sdl (ha itt hívjuk)

#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>


/*
Inicializálja az alkalmazást:
 - SDL és OpenGL környezet beállítása
 - Ablak létrehozása
 - Textúra-kezelők inicializálása
 - Kamera és jelenet inicializálása
*/
    void init_app(App* app, int width, int height) {
        int error_code;
        int inited_loaders;

        app->is_running = false;

        error_code = SDL_Init(SDL_INIT_EVERYTHING);
        if (error_code != 0) {
            printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
            return;
        }

        app->window = SDL_CreateWindow(
            "Hadesz!",
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

    // OpenGL beállítások
        init_opengl();
        reshape(width, height);

    // Játékállapot, menü, kamera, jelenet inicializálása
        game_state_init(&(app->game_state));            // Inicializálja a GameState-et (benne az Eloszoba is)
        menu_init(&(app->menu));                        // Inicializálja a Menüt
        init_camera(&(app->camera));                    // Inicializálja a Kamerát
        init_scene(&(app->scene));  // Inicializálja a Jelenetet (átadja a GameState-et a fényerőhöz)
    
    // Fény mozgásával kapcsolatos változók inicializálása
    app->brightness =128;    
    app->light_move_speed = 0.5f;
        app->move_light_x = 0;
        app->move_light_y = 0;
        app->move_light_z = 0;
    
        app->uptime = (double)SDL_GetTicks() / 1000.0;
        app->is_running = true;
    }
    
/*
OpenGL beállításokat végző függvény:
 - világítás, árnyékolás, mélységi teszt, textúrák engedélyezése stb.
*/
    void init_opengl() {
        glShadeModel(GL_SMOOTH);

        glEnable(GL_NORMALIZE);
        glEnable(GL_AUTO_NORMAL);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Use float literals

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_DEPTH_TEST);

        glClearDepth(1.0);

        glEnable(GL_TEXTURE_2D);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }

/*
Átméretezi a viewport-ot, mikor változik az ablak mérete
 - Megtartja a megadott képarányt
 - Beállítja a vetítési mátrixot (perspektíva)
*/
    void reshape(GLsizei width, GLsizei height) {
        int x, y, w, h;
        double ratio;

        ratio = (double)width / height;
        if (ratio > VIEWPORT_RATIO) {
            w = (int)((double)height * VIEWPORT_RATIO);
            h = height;
            x = (width - w) / 2;
            y = 0;
        } else {
            w = width;
            h = (int)((double)width / VIEWPORT_RATIO);
            x = 0;
            y = (height - h) / 2;
        }

        glViewport(x, y, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(
            -.08, .08,
            -.06, .06,
            .1, 10
        );
    }

/*
Felhasználói események kezelése (billentyűzet, egér, bezárás stb.)
 - Kamera mozgatása gombnyomásokra
 - Kilépés ESC vagy ablak bezárásra
*/
   void handle_app_events(App* app){
    // Létrehozunk egy InputContext-et és inicializáljuk a szükséges pointerekkel
    InputContext input_ctx;
    input_init(&input_ctx, &(app->game_state), &(app->menu), &(app->camera), app);

    while (SDL_PollEvent(&(app->event))) {
        // Továbbítjuk az eseményt az input kezelőnek
        input_handle_event(&input_ctx, &(app->event));

        // Specifikus App események, amiket az input_handle_event nem feltétlenül kezel közvetlenül
        switch (app->event.type) {
            case SDL_QUIT:
                app->is_running = false;
                break;
            case SDL_WINDOWEVENT:
                if (app->event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    app->window_width = app->event.window.data1;
                    app->window_height = app->event.window.data2;
                    reshape(app->window_width, app->window_height);
                }
                break;
            // Az SDL_TEXTINPUT eseményt az input_handle_event már továbbítja az eloszoba_handle_event hívásával.
            // Itt csak azt kellene kezelni, hogy mikor START/STOP a text input.
            case SDL_KEYDOWN:
                // Ha a játék az Eloszoba állapotban van és a felhasználó Entert nyomott,
                // vagy más módon aktiválni/deaktiválni kell a szövegbevitelt
                if (app->game_state.current_enum_state == GAME_STATE_ELOSZOBA) {
                    if (app->event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                        // Itt lehetne SDL_StopTextInput() ha befejezte a bevitelt,
                        // vagy ellenőrizni, hogy aktív-e már.
                        // Jelenlegi beállítással az eloszoba_handle_event kezeli a bevitelt.
                    } else {
                        SDL_StartTextInput(); // Folyamatosan engedélyezzük a szövegbevitelt Eloszoba módban
                    }
                } else {
                    SDL_StopTextInput(); // Más állapotokban tiltsuk le a szövegbevitelt
                }
                break;
            default:
                break;
        }
    }
}

/*
Az alkalmazás logikai frissítése (pl. idő alapú mozgások)
 - Kamera és jelenet frissítése az eltelt idő alapján
*/
    void update_app(App* app) {
        double current_time;
        double elapsed_time;

        current_time = (double)SDL_GetTicks() / 1000.0; 
        elapsed_time = current_time - app->uptime;
        app->uptime = current_time;

        update_camera(&(app->camera), elapsed_time);
        update_scene(&(app->scene), app, elapsed_time);
    }

/*
Az alkalmazás kirajzolása a képernyőre
 - Kamera nézet beállítása és jelenet megjelenítése
 - Előnézeti textúra kirajzolása (ha szükséges)
 - Képkocka megjelenítése a képernyőn
*/
    void render_app(App* app) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        set_view(&(app->camera));
        render_scene(&(app->scene));
        glPopMatrix();

        if (app->camera.is_preview_visible) {
            show_texture_preview();
        }

        SDL_GL_SwapWindow(app->window);
    }

/*
Az alkalmazás erőforrásainak felszabadítása
 - OpenGL kontextus törlése
 - Ablak bezárása
 - SDL leállítása
*/
    void destroy_app(App* app) {
        if (app->gl_context != NULL) {
            SDL_GL_DeleteContext(app->gl_context);
            app->gl_context = NULL; // Fontos, hogy NULL-ra állítsuk felszabadítás után
        }

        if (app->window != NULL) {
            SDL_DestroyWindow(app->window);
        }
        destroy_scene(&(app->scene));

        SDL_Quit();
        IMG_Quit();
    }