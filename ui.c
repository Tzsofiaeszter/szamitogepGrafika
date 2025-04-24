#include "ui.h"
#include <stdio.h>
#include <SDL2/SDL_ttf.h>   // színes szöveg megjelenítéséhez kellenek
#include <SDL2/SDL.h>

void ui_render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void ui_render_minimap(SDL_Renderer* renderer, int current_room, bool solved_rooms[4], int x, int y, const char* room_names[4], TTF_Font* font) {
    const int room_size = 30;
    const int spacing = 15;
// Szobák pozíciói
    SDL_Point positions[4] = {
        {x, y - room_size - spacing},
        {x + room_size + spacing, y},
        {x, y + room_size + spacing},
        {x - room_size - spacing, y}
    };

    for (int i = 0; i < 4; i++) {
        SDL_Rect rect = {positions[i].x, positions[i].y, room_size, room_size};
// Szobák színe
        if (i == current_room)
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);      // Zöld: aktuális
        else if (solved_rooms[i])
            SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);    // Kék: megoldott
        else
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);  // Szürke: zárt

        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Fehér keret
        SDL_RenderDrawRect(renderer, &rect);
// Szobák neve
        int text_x = positions[i].x + (room_size / 2) - (strlen(room_names[i]) * 4); // Középre igazítás
        int text_y = positions[i].y + (room_size / 2) - 10; // Vertikálisan a közepére helyezzük
        ui_render_text(renderer, font, room_names[i], text_x, text_y);
    }
}

void ui_render_minimap_overlay(SDL_Renderer* renderer, TTF_Font* font, int current_room, bool solved_rooms[4], int win_w, int win_h, bool show, const char* room_names[4]) {
    if (!show) return;
// Háttér overlay (átlátszó fekete)
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_Rect bg = {win_w / 4, win_h / 4, win_w / 2, win_h / 2};
    SDL_RenderFillRect(renderer, &bg);
// Térkép kirajzolása
    int map_center_x = win_w / 2;
    int map_center_y = win_h / 2;
    ui_render_minimap(renderer, current_room, solved_rooms, map_center_x, map_center_y, room_names, font);
// Cím
    ui_render_text(renderer, font, "🗺️ Térkép:", map_center_x - 40, bg.y + 10);
}

void ui_render_room_info(SDL_Renderer* renderer, TTF_Font* font, const char* room_name, bool solved, int x, int y) {
    char buffer[128];
    sprintf(buffer, "Szoba: %s [%s]", room_name, solved ? "Megoldva" : "Folyamatban");
    ui_render_text(renderer, font, buffer, x, y);
}

void ui_render_message(SDL_Renderer* renderer, TTF_Font* font, const char* message, int x, int y) {
    ui_render_text(renderer, font, message, x, y);
}

void ui_render_key_status(SDL_Renderer* renderer, TTF_Font* font, int keys_collected, int total_keys, int x, int y) {
    char buffer[64];
    sprintf(buffer, "Kulcsok: %d / %d", keys_collected, total_keys);
    ui_render_text(renderer, font, buffer, x, y);
}

void ui_render_minimap(SDL_Renderer* renderer, int current_room, bool solved_rooms[4], int x, int y) {
    const int room_size = 30;
    const int spacing = 15;

    SDL_Point positions[4] = {
        {x, y - room_size - spacing},
        {x + room_size + spacing, y},
        {x, y + room_size + spacing},
        {x - room_size - spacing, y}
    };

    for (int i = 0; i < 4; i++) {
        SDL_Rect rect = {positions[i].x, positions[i].y, room_size, room_size};

        if (i == current_room)
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);      // Zöld: aktuális
        else if (solved_rooms[i])
            SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);    // Kék: megoldott
        else
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);  // Szürke: zárt

        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Fehér keret
        SDL_RenderDrawRect(renderer, &rect);
    }
}

// Felugró overlay verzió
void ui_render_minimap_overlay(SDL_Renderer* renderer, TTF_Font* font, int current_room, bool solved_rooms[4], int win_w, int win_h, bool show) {
    if (!show) return;

    // Háttér overlay (átlátszó fekete)
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_Rect bg = {win_w / 4, win_h / 4, win_w / 2, win_h / 2};
    SDL_RenderFillRect(renderer, &bg);

    // Térkép
    int map_center_x = win_w / 2;
    int map_center_y = win_h / 2;
    ui_render_minimap(renderer, current_room, solved_rooms, map_center_x, map_center_y);

    // Cím
    ui_render_text(renderer, font, "🗺️ Térkép:", map_center_x - 40, bg.y + 10);
}

// szövegszínezés
void ui_render_text_colored(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dst = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}