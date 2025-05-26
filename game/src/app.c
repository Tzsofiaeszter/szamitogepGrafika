#include "app.h"
#include "render.h"
#include "scene.h"
#include "light.h"

#include <stdio.h>
#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height){
    printf("[DEBUG] init_app eleje - is_running: %d\n", app->is_running);
    int error_code;
    int inited_loaders;


    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        printf("[DEBUG] kilépés SDL_Init-nél\n");
        return;
        }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
   
    app->window = SDL_CreateWindow(
        "Game!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        printf("[DEBUG] kilépés IMG_Init-nél\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        printf("[DEBUG] kilépés SDL_CreateWindow-nél\n");
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context: %s\n", SDL_GetError());
          printf("[DEBUG] kilepes SDL_GL_CreateContext-nel false eseteben\n");
        //app->is_running = false;
        return;
    } else {
        printf("[INFO] OpenGL context created successfully.\n");
        printf("[INFO] OpenGL version: %s\n", glGetString(GL_VERSION));
        printf("[DEBUG] kilepes SDL_GL_CreateContext-nel\n");
    }

    // Initialize window dimensions in the App struct
    app->window_width = width;
    app->window_height = height;

    init_opengl();
        printf("init_opengl() lefutott\n");

    reshape(width, height);
        printf("reshape() lefutott\n");

    init_camera(&(app->camera));
       printf("init_camera() után\n");

    init_scene(&(app->scene));
        printf("init_scene() után\n");

    // Light initialization
    app->brightness = 150; // Initial brightness value
    // Assuming 'light' is a member of the 'Scene' struct, e.g., Scene.light
    app->scene.light.id = GL_LIGHT0; // Assign the OpenGL light ID (e.g., GL_LIGHT0)
    app->scene.light.position[0] = 1.0f; // X component of light position
    app->scene.light.position[1] = 1.0f; // Y component of light position
    app->scene.light.position[2] = 1.0f; // Z component of light position
    app->scene.light.position[3] = 0.0f; // W component: 0.0f for directional light, 1.0f for positional light

    // Initialize the light with its properties
    init_light(&(app->scene.light));
        printf("init_light() után\n");
    // Set the initial brightness of the light
    set_light_brightness(&(app->scene.light), app->brightness);
        printf("set_light_brightness() után\n");

    app->is_running = true;
    printf("init_app() befejezve, is_running = %d\n", app->is_running);

}

void init_opengl() {
    // Alap beállítások
    glEnable(GL_DEPTH_TEST);          // Mélységi teszt a 3D megjelenítéshez
    glClearDepth(1.0);                // Mélységi puffer alapértelmezett értéke

    // Textúrázás
    glEnable(GL_TEXTURE_2D);          // 2D textúrák engedélyezése

    // Világítás
    glEnable(GL_LIGHTING);            // Globális világítás engedélyezése
    glEnable(GL_LIGHT0);              // Legalább 1 fényforrás bekapcsolása

    // Anyagkezelés
    glEnable(GL_COLOR_MATERIAL);      // Anyag színének automatikus kezelése

    // Normálvektor automatikus beállítása és normalizálása
    glEnable(GL_NORMALIZE);           // Skálázott modelleknél fontos
    glEnable(GL_AUTO_NORMAL);         // Bézier felületekhez, de nem árt itt sem

    // Árnyalás
    glShadeModel(GL_SMOOTH);          // Folyamatos árnyalás (szebb)

    // Háttérszín
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Sötétszürke háttér (nem fekete)
}

void handle_app_events(App *app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
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
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_Z:
                set_camera_topview(&(app->camera));
                break;
            case SDL_SCANCODE_X:
                set_camera_sideview(&(app->camera));
                break;
            case SDL_SCANCODE_Y:
                set_camera_frontview(&(app->camera));
                break;
            case SDL_SCANCODE_R:
                init_camera(&(app->camera));
                break;
            case SDL_SCANCODE_F1:
                app->scene.segedkepernyo_texture = !(app->scene.segedkepernyo_texture);
                break;
            case SDL_SCANCODE_UP:
                app->scene.platform_scale_z += 0.1f;
                if (app->scene.platform_scale_z > 1.0f)
                {
                    app->scene.platform_scale_z = 1.0f;
                }
                break;
            case SDL_SCANCODE_DOWN:
                app->scene.platform_scale_z -= 0.1f;
                if (app->scene.platform_scale_z < 0.05f)
                {
                    app->scene.platform_scale_z = 0.05f;
                }
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down)
            {
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
        -.08, .08,
        -.06, .06,
        .1, 10
    );
}

void update_app(App* app){
    //render_app(app); 
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));
}

void render_app(App* app) {
   
   printf("[DEBUG] render_app() eleje\n");
    // 1. Képernyő törlés (fontos az égbolt után!)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 2. Égbolt megjelenítése (ortho nézetben, textúra háttérként)
    draw_background(app, app->scene.eg_background_texture);

    // 3. Kamera frissítése és nézet beállítása
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double current_time = (double)SDL_GetTicks() / 1000;
    update_camera(&(app->camera), current_time - app->uptime);
    set_view(&(app->camera));

    // 4. Jelenet renderelése (3D objektumok, világítás stb.)
    glPushMatrix();
    render_scene(&(app->scene));
    glPopMatrix();

    // 5. Segédképernyő megjelenítése F1-re (mindent lefed)
    if (app->camera.is_preview_visible) {
        render_help_screen(app);
    }

    // 6. Rajzolás befejezése és képernyő frissítése
    glFlush();
    SDL_GL_SwapWindow(app->window);

    printf("[DEBUG] render_app() vege\n");
}

void destroy_app(App* app){
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}