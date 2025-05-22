#ifndef APP_H
#define APP_H


#include <SDL2/SDL.h>
#include <stdbool.h>
#include <GL/gl.h>

#include "game_state.h"  
#include "menu.h" 
#include "camera.h"
#include "scene.h"
#include "scene_manager.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

typedef struct App {
    SDL_Window* window;
    SDL_GLContext gl_context;
    SDL_Event event;

    bool is_running;
    double uptime;
    
    GameState game_state;
    Menu menu;
    //SceneManager* scene_manager;

    Camera camera;
    Scene scene;

    int brightness;

    float light_move_speed;
    int move_light_x;
    int move_light_y;
    int move_light_z;

    int window_width;
    int window_height;
} App;


void init_opengl(void); // OpenGL alapbeállítások
void reshape(GLsizei width, GLsizei height); // Nézetablak átméretezése

void init_app(App* app, int width, int height); // Az alkalmazás inicializálása
void handle_app_events(App* app); // Az alkalmazás eseményeinek kezelése
void update_app(App* app);        // Az alkalmazás logikájának frissítése
void render_app(App* app);        // Az alkalmazás kirajzolása
void destroy_app(App* app);       // Az alkalmazás erőforrásainak felszabadítása


#endif 
