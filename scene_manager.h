/*
A scene manager célja, hogy kezelje a különböző szobák közötti váltásokat, tehát a 
játékmenet során egy szobából a következőbe léphessen a játékos, ha megoldotta a szükséges rejtvényeket
*/

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "puzzle.h"
#include"eloszoba.h"

#define MAX_ROOMS 4

const char* room_names[4] = {
    "Eloszoba",
    "Nappali",
    "Konyha",
    "Furdoszoba",
    "Szoba";
};

typedef struct Room {
    Puzzle* puzzle;
    bool puzzle_solved;
    const char* name;
} Room;


typedef struct SceneManager{
    Room rooms[MAX_ROOMS];
    int current_room;
    int total_rooms;

    Eloszoba eloszoba;
    char kod_input[5];
    int kod_length;
} SceneManager;



SceneManager* scene_manager_create();
void scene_manager_free(SceneManager* manager);
void scene_manager_next_room(SceneManager* manager);
void scene_manager_render(SceneManager* manager, SDL_Renderer* renderer, TTF_Font* font);
void scene_manager_update(SceneManager* manager);

#endif // SCENE_MANAGER_H