/*
A scene manager célja, hogy kezelje a különböző szobák közötti váltásokat, tehát a 
játékmenet során egy szobából a következőbe léphessen a játékos, ha megoldotta a szükséges rejtvényeket
*/

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "puzzle.h"
#include "eloszoba.h"
#include "game_state.h"

#define MAX_ROOMS 4

const char* room_names[4]; 

typedef struct {
    Puzzle* puzzle;
    bool puzzle_solved;
    const char* name;

    // új mezők a szobához tartozó viselkedéshez
    void (*init)(Eloszoba* eloszoba);
    void (*render)(SDL_Renderer* renderer, Eloszoba* eloszoba);
    void (*handle_input)(SDL_Event* event, Eloszoba* eloszoba, char* kod_input, size_t* kod_length, GameState* game_state);
    void (*cleanup)(Eloszoba* eloszoba);
}Room;



typedef struct {
    Room rooms[MAX_ROOMS];
    size_t current_room;
    size_t total_rooms;

    Eloszoba eloszoba;
    char kod_input[6];
    size_t kod_length;
    GameState game_state;
}SceneManager;

SceneManager* scene_manager_create();
void scene_manager_free(SceneManager* manager);
void scene_manager_next_room(SceneManager* manager);
void scene_manager_update(SceneManager* manager);
void scene_manager_handle_event(SceneManager* manager, SDL_Event* event, GameState* game_state);
#endif