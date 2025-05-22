/*
#include "animation.h"
#include <stdlib.h> // rand()
#include <GL/gl.h>  // OpenGL függvények

// Részecskék inicializálása
void init_reszecskek(AnimationState* animState) {
    for (int i = 0; i < RESZECSKESZAM; ++i) {
        animState->reszecskek[i].x = 0.0f;
        animState->reszecskek[i].y = 0.0f;
        animState->reszecskek[i].z = 0.0f;
        animState->reszecskek[i].vx = (float)(rand() % 200 - 100.0f) / 1000.0f;
        animState->reszecskek[i].vy = (float)(rand() % 200) / 1000.0f;
        animState->reszecskek[i].vz = (float)(rand() % 200 - 100.0f) / 1000.0f;
        animState->reszecskek[i].life = (float)(rand() % 100) / 100.0f + 1.0f;
        animState->reszecskek[i].color[0] = 1.0f; // Red
        animState->reszecskek[i].color[1] = 0.5f + (float)(rand() % 50) / 100.0f; // Orange to Yellow
        animState->reszecskek[i].color[2] = 0.0f; // Black
        animState->reszecskek[i].color[3] = 1.0f; // Alpha
    }
}

// Animáció állapotának inicializálása
void init_animation_state(AnimationState* animState) {
    animState->tuzIdo = 0.0f;
    animState->ajtoNyitasSzog = 0.0f;
    animState->ajtoNyitva = 0;
    init_reszecskek(animState); // Inicializáljuk a részecskéket is
}

// Részecskék frissítése
void update_reszecskek(AnimationState* animState, float deltaTime) {
    for (int i = 0; i < RESZECSKESZAM; ++i) {
        animState->reszecskek[i].x += animState->reszecskek[i].vx * deltaTime;
        animState->reszecskek[i].y += animState->reszecskek[i].vy * deltaTime;
        animState->reszecskek[i].z += animState->reszecskek[i].vz * deltaTime;
        animState->reszecskek[i].life -= deltaTime;
        if (animState->reszecskek[i].life < 0.0f) {
            animState->reszecskek[i].x = 0.0f;
            animState->reszecskek[i].y = 0.0f;
            animState->reszecskek[i].z = 0.0f;
            animState->reszecskek[i].vx = (float)(rand() % 200 - 100.0f) / 1000.0f;
            animState->reszecskek[i].vy = (float)(rand() % 200) / 1000.0f;
            animState->reszecskek[i].vz = (float)(rand() % 200 - 100.0f) / 1000.0f;
            animState->reszecskek[i].life = (float)(rand() % 100) / 100.0f + 1.0f;
            animState->reszecskek[i].color[0] = 1.0f; // Red
            animState->reszecskek[i].color[1] = 0.5f + (float)(rand() % 50) / 100.0f; // Orange to Yellow
            animState->reszecskek[i].color[2] = 0.0f; // Black
            animState->reszecskek[i].color[3] = 1.0f; // Alpha
        }
    }
}

// Részecskék kirajzolása
void draw_reszecskek(const AnimationState* animState) {
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f); // Feltételezve, hogy ez a kandalló helye
    glBegin(GL_QUADS);
    for (int i = 0; i < RESZECSKESZAM; ++i) {
        if (animState->reszecskek[i].life > 0.0f) {
            glColor4f(animState->reszecskek[i].color[0], animState->reszecskek[i].color[1],
                      animState->reszecskek[i].color[2], animState->reszecskek[i].life); // Alpha fade
            // A részecskék textúrázott négyzetek lehetnének a tűz effektushoz
            // Itt most csak egyszerű négyzeteket rajzolunk
            float size = 0.05f * animState->reszecskek[i].life; // Méret csökken az élettartammal
            glVertex3f(animState->reszecskek[i].x - size, animState->reszecskek[i].y - size, animState->reszecskek[i].z);
            glVertex3f(animState->reszecskek[i].x + size, animState->reszecskek[i].y - size, animState->reszecskek[i].z);
            glVertex3f(animState->reszecskek[i].x + size, animState->reszecskek[i].y + size, animState->reszecskek[i].z);
            glVertex3f(animState->reszecskek[i].x - size, animState->reszecskek[i].y + size, animState->reszecskek[i].z);
        }
    }
    glEnd();
    glPopMatrix();
}


// Animációk frissítése az idő függvényében
void update_animations(AnimationState* animState, float deltaTime) {
    // Kandallótűz animációja
    update_reszecskek(animState, deltaTime);
    
    // Ajtó animációja
    if (animState->ajtoNyitva) {
        if (animState->ajtoNyitasSzog < 90.0f) {
            animState->ajtoNyitasSzog += 90.0f * deltaTime;
            if (animState->ajtoNyitasSzog > 90.0f) { // Ne menjen túl 90 fokon
                animState->ajtoNyitasSzog = 90.0f;
            }
        }
    } else {
        if (animState->ajtoNyitasSzog > 0.0f) {
            animState->ajtoNyitasSzog -= 90.0f * deltaTime;
            if (animState->ajtoNyitasSzog < 0.0f) { // Ne menjen 0 fok alá
                animState->ajtoNyitasSzog = 0.0f;
            }
        }
    }
}

*/













