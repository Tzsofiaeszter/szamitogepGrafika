#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_CIRCLE_COUNT 50
#define PI 3.14159265358979323846

typedef struct {
    int x, y, radius;
    Uint8 r, g, b;
} Circle;

Circle circles[MAX_CIRCLE_COUNT];
int circle_count = 0;
bool dragging = false;
int dragged_index = -1;

void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void draw_circle(SDL_Renderer *renderer, Circle circle, int segments) {
    float angle_step = (2 * PI) / segments;
    for (int i = 0; i < segments; i++) {
        float theta1 = i * angle_step;
        float theta2 = (i + 1) * angle_step;
        int x1 = circle.x + cos(theta1) * circle.radius;
        int y1 = circle.y + sin(theta1) * circle.radius;
        int x2 = circle.x + cos(theta2) * circle.radius;
        int y2 = circle.y + sin(theta2) * circle.radius;
        draw_line(renderer, x1, y1, x2, y2, circle.r, circle.g, circle.b);
    }
}

void draw_cross(SDL_Renderer *renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, x - 5, y, x + 5, y);
    SDL_RenderDrawLine(renderer, x, y - 5, x, y + 5);
}

int is_cursor_inside_circle(int x, int y, Circle circle) {
    int dx = x - circle.x;
    int dy = y - circle.y;
    return (dx * dx + dy * dy) <= (circle.radius * circle.radius);
}

void handle_mouse_click(int x, int y) {
    for (int i = 0; i < circle_count; i++) {
        if (is_cursor_inside_circle(x, y, circles[i])) {
            dragging = true;
            dragged_index = i;
            return;
        }
    }
    if (circle_count < MAX_CIRCLE_COUNT) {
        circles[circle_count++] = (Circle){x, y, 50, rand() % 256, rand() % 256, rand() % 256};
    }
}

void handle_mouse_motion(int x, int y) {
    if (dragging && dragged_index != -1) {
        circles[dragged_index].x = x;
        circles[dragged_index].y = y;
    }
}

void handle_mouse_release() {
    dragging = false;
    dragged_index = -1;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Kör Rajzoló", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                handle_mouse_click(e.button.x, e.button.y);
            } else if (e.type == SDL_MOUSEMOTION) {
                handle_mouse_motion(e.motion.x, e.motion.y);
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                handle_mouse_release();
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < circle_count; i++) {
            draw_circle(renderer, circles[i], 36);
            if (is_cursor_inside_circle(mouse_x, mouse_y, circles[i])) {
                draw_cross(renderer, circles[i].x, circles[i].y);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
