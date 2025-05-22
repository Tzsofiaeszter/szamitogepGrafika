#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "game_state.h"  
#include "menu.h"       
#include "camera.h"     
#include "app.h"

// Előre deklarációk a struktúrákhoz, amiket az InputContext használ
struct GameState;
struct Menu;
struct Camera;
struct App; // Az App struktúra előre deklarálása

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
    bool enter;
    bool plus;
    bool minus;
    bool n;  // Hozzáadva az 'n' billentyűhöz
    bool p;  // Hozzáadva a 'p' billentyűhöz
    bool F1; // Hozzáadva az 'F1' billentyűhöz
    bool F2; // Hozzáadva az 'F2' billentyűhöz
    bool F3; // Hozzáadva az 'F3' billentyűhöz

    // Tagok a fény mozgatásához
    bool move_light_x_neg;
    bool move_light_x_pos;
    bool move_light_y_neg;
    bool move_light_y_pos;
    bool move_light_z_neg;
    bool move_light_z_pos;

} KeyState;

// InputContext struktúra az input kezeléshez szükséges állapotok pointereinek tárolására
typedef struct {
    KeyState key_state;
     GameState* game_state;
     Menu* menu;
     Camera* camera; // Hozzáadva a kamera állapot pointere
     App* app;       // Hozzáadva az App állapot pointere
} InputContext;

// Függvény prototípusok
void key_state_update(SDL_Event* event, KeyState* key_state);

void input_init(InputContext* ctx, GameState* state, Menu* menu, Camera* camera, App* app);
void input_handle_event(InputContext* ctx, const SDL_Event* event);


#endif 