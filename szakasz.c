#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_LINE_COUNT 100
#define PALETTE_SIZE 5

typedef struct {
    Uint8 r, g, b;
} Color;

typedef struct {
    int x1, y1, x2, y2;
    Color color;
} Line;

typedef struct {
    int x, y, width, height;
    Color color;
} Rectangle;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Line lines[MAX_LINE_COUNT];
Rectangle rectangles[MAX_LINE_COUNT];
int line_count = 0;
int rect_count = 0;
bool drawing_line = true;
Color selected_color = {255, 255, 255};
Color palette[PALETTE_SIZE] = {
    {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0}, {255, 165, 0}
};

typedef struct {
    int x, y, width, height;
    Color color;
} PaletteBox;

PaletteBox color_palette[PALETTE_SIZE];

void init_palette() {
    for (int i = 0; i < PALETTE_SIZE; i++) {
        color_palette[i].x = 10 + i * 50;
        color_palette[i].y = 10;
        color_palette[i].width = 40;
        color_palette[i].height = 40;
        color_palette[i].color = palette[i];
    }
}

void render_palette() {
    for (int i = 0; i < PALETTE_SIZE; i++) {
        SDL_SetRenderDrawColor(renderer, color_palette[i].color.r, color_palette[i].color.g, color_palette[i].color.b, 255);
        SDL_Rect rect = {color_palette[i].x, color_palette[i].y, color_palette[i].width, color_palette[i].height};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void render_lines() {
    for (int i = 0; i < line_count; i++) {
        SDL_SetRenderDrawColor(renderer, lines[i].color.r, lines[i].color.g, lines[i].color.b, 255);
        SDL_RenderDrawLine(renderer, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
    }
}

void render_rectangles() {
    for (int i = 0; i < rect_count; i++) {
        SDL_SetRenderDrawColor(renderer, rectangles[i].color.r, rectangles[i].color.g, rectangles[i].color.b, 255);
        SDL_Rect rect = {rectangles[i].x, rectangles[i].y, rectangles[i].width, rectangles[i].height};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void handle_mouse_click(int x, int y) {
    for (int i = 0; i < PALETTE_SIZE; i++) {
        if (x >= color_palette[i].x && x <= color_palette[i].x + color_palette[i].width &&
            y >= color_palette[i].y && y <= color_palette[i].y + color_palette[i].height) {
            selected_color = color_palette[i].color;
            return;
        }
    }

    static int click_count = 0;
    static int x1, y1;

    if (drawing_line) {
        if (click_count == 0) {
            x1 = x;
            y1 = y;
            click_count = 1;
        } else {
            if (line_count < MAX_LINE_COUNT) {
                lines[line_count++] = (Line){x1, y1, x, y, selected_color};
            }
            click_count = 0;
        }
    } else {
        if (rect_count < MAX_LINE_COUNT) {
            rectangles[rect_count++] = (Rectangle){x, y, 50, 50, selected_color};
        }
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Szakasz és Téglalap Rajzoló", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    init_palette();

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                printf("Egérpozíció: x=%d, y=%d\n", x, y);
                handle_mouse_click(x, y);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    drawing_line = !drawing_line;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_palette();
        render_lines();
        render_rectangles();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
