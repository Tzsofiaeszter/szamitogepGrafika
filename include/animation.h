/*
#ifndef ANIMATION_H
#define ANIMATION_H

#include <GL/gl.h> // Szükséges a GLuint és GLfloat miatt

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float color[4];
    float life;
} Reszecske;

#define RESZECSKESZAM 100

// Új struktúra az animáció állapotának tárolására
typedef struct {
    float tuzIdo;
    float ajtoNyitasSzog;
    int ajtoNyitva;
    Reszecske reszecskek[RESZECSKESZAM];
} AnimationState;

// Függvények szignatúrái
void init_animation_state(AnimationState* animState);
void update_animations(AnimationState* animState, float deltaTime);
void draw_reszecskek(const AnimationState* animState); // drawReszecskek átnevezve draw_reszecskek-re
void init_reszecskek(AnimationState* animState); // initReszecskek átnevezve init_reszecskek-re
void update_reszecskek(AnimationState* animState, float deltaTime); // updateReszecskek átnevezve update_reszecskek-re

#endif 
*/