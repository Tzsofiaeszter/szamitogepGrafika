#ifndef APP_H
#define APP_H


#include <SDL2/SDL.h>
#include <stdbool.h>
#include <GL/gl.h>

#include "game_state.h"   
#include "scene_manager.h"
#include "camera.h"
#include "scene.h"
#include "menu.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

typedef struct {
    SDL_Window* window;
    SDL_GLContext gl_context;
    bool is_running;
    double uptime;

    SDL_Event event;
 
    
    GameState game_state;
    Menu menu;
    SceneManager* scene_manager;

    Camera camera;
    Scene scene;
} App;


void init_opengl(void);
void reshape(GLsizei width, GLsizei height);

bool initialize_app(App* app);
void init_app(App* app, int width, int height);
void handle_app_events(App* app, SDL_Event* event);
void update_app(App* app);
void render_app(App* app);
void destroy_app(App* app);

#endif 
