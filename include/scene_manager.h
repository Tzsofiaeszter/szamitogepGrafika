/*
A scene manager célja, hogy kezelje a különböző szobák közötti váltásokat, tehát a 
játékmenet során egy szobából a következőbe léphessen a játékos, ha megoldotta a szükséges rejtvényeket
*/

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "puzzle_logic.h" // PuzzleRoom
#include "eloszoba.h"     // EloszobaData
#include "game_state.h"   // GameState

#include <SDL2/SDL.h>

/*
// Szoba típusok
typedef enum {
    ROOM_TYPE_ELOSZOBA,
    //ROOM_TYPE_NAPPALI,
} RoomType;
*/

/*
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
*/


typedef struct SceneManager{
    RoomID current_room_id;             // Az aktuális szoba azonosítója
    int total_rooms;                    // Összes szoba száma

    PuzzleRoom rooms[ROOM_COUNT];        // A szobák adatai (benne a puzzle is)
}SceneManager;

SceneManager* scene_manager_create();
void scene_manager_update(SceneManager* manager, GameState* game_state);
void scene_manager_render(const SceneManager* manager, SDL_Renderer* renderer);
void scene_manager_handle_event(SceneManager* manager, const SDL_Event* event, GameState* game_state);
void scene_manager_destroy(SceneManager* manager);

#endif