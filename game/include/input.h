/*
#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
     
#include "camera.h"     
#include "app.h"

// KeyState struktúra a billentyűk állapotának tárolására
typedef struct {
    bool escape;
    bool h;
    bool w;
    bool s;
    bool a;
    bool d;
    bool up;
    bool down;
    bool left;
    bool right;
    bool plus;
    bool minus;
    bool F1; 

// Tagok a fény mozgatásához
    bool move_light_x_neg;
    bool move_light_x_pos;
    bool move_light_y_neg;
    bool move_light_y_pos;
    bool move_light_z_neg;
    bool move_light_z_pos;

} KeyState;

typedef struct {
    KeyState key_state;
    Camera* camera;
    App* app;
} InputContext;



// Függvény prototípusok
void input_init(InputContext* ctx, void* unused1, void* unused2, Camera* camera, App* app);
void input_handle_event(InputContext* ctx, const SDL_Event* event);
void key_state_update(SDL_Event* event, KeyState* key_state);



#endif 
*/