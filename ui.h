#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

void ui_render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
void ui_render_room_info(SDL_Renderer* renderer, TTF_Font* font, const char* room_name, bool solved, int x, int y);// Szoba információ renderelése (név + megoldva-e
void ui_render_message(SDL_Renderer* renderer, TTF_Font* font, const char* message, int x, int y);// Egyéni üzenetek kirajzolása
void ui_render_key_status(SDL_Renderer* renderer, TTF_Font* font, int keys_collected, int total_keys, int x, int y);// Megszerzett kulcsok állapotának kiírása
void ui_render_minimap(SDL_Renderer* renderer, int current_room, bool solved_rooms[4], int x, int y);// Egyszerű térkép megjelenítése 

// Felugró minimap overlay
void ui_render_minimap_overlay(SDL_Renderer* renderer, TTF_Font* font, int current_room, bool solved_rooms[4], int win_w, int win_h, bool show);

#endif
