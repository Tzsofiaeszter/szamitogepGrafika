#pragma once   // - a fordítás során csak eygsezr szabad felhasználni

#include <SDL2/SDL.h>

void game_init();                           // A játék inicializálása (erőforrások betöltése, kezdőállapot)
void game_update();                         // A játék aktuális logikájának frissítése
void game_handle_event(SDL_Event* event);   // Események (input) kezelése – például SDL billentyűleütések
void game_cleanup();                        // A játék erőforrásainak felszabadítása
bool game_is_running();                     // Ellenőrzi, hogy a játék még fut-e (főciklusban használandó)
