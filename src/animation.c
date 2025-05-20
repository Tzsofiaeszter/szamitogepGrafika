/*#include "animation.h"
#include"eloszoba.h"


// Globális változók az animációkhoz

float tuzIdo = 0.0f;
float ajtoNyitasSzog = 0.0f;
int ajtoNyitva = 0;
void updateReszecskek(float deltaTime);

void updateAnimations(float deltaTime) {// Animációk frissítése az idő függvényében
    // Kandallótűz animációja
        updateReszecskek(deltaTime);
    
    // Ajtó animációja
        if (ajtoNyitva) {
            if (ajtoNyitasSzog < 90.0f) {
                ajtoNyitasSzog += 90.0f * deltaTime;
            }
        } else {
            if (ajtoNyitasSzog > 0.0f) {
                ajtoNyitasSzog -= 90.0f * deltaTime;
            }
        }
    }
    

// Részecske struktúra a TŰZhöz
        typedef struct {
            float x, y, z;
            float vx, vy, vz;
            float color[4];
            float life;
        } Reszecske;

        #define RESZECSKESZAM 100
        Reszecske reszecskek[RESZECSKESZAM];

        void initReszecskek() {
            for (int i = 0; i < RESZECSKESZAM; i++) {
                reszecskek[i].x = 0.0f;
                reszecskek[i].y = 0.0f;
                reszecskek[i].z = 0.0f;
                
                reszecskek[i].vx = (rand() % 200 - 100.0f) / 1000.0f;       // random szám generálás az x koordinátának
                reszecskek[i].vy = (rand() % 200) / 1000.0f;                // v= vízszintes mozgás sebességét állítja be = véletlenszerű mozgást biztosít
                reszecskek[i].vz = (rand() % 200 - 100.0f) / 1000.0f;
            
                reszecskek[i].color[0] = 1.0f;      // x koordináta
                reszecskek[i].color[1] = 0.5f;      // y koordináta
                reszecskek[i].color[2] = 0.0f;      // z koordináta
                reszecskek[i].color[3] = 1.0f;      // w koordináta
                
                reszecskek[i].life = (rand() % 100) / 100.0f + 1.0f;
            }
        }

        void updateReszecskek(float deltaTime) {
            for (int i = 0; i < RESZECSKESZAM; i++) {
                reszecskek[i].x += reszecskek[i].vx * deltaTime;
                reszecskek[i].y += reszecskek[i].vy * deltaTime;
                reszecskek[i].z += reszecskek[i].vz * deltaTime;
                reszecskek[i].life -= deltaTime;
                if (reszecskek[i].life < 0.0f) {
                    reszecskek[i].x = 0.0f;
                    reszecskek[i].y = 0.0f;
                    reszecskek[i].z = 0.0f;
                    reszecskek[i].vx = (rand() % 200 - 100.0f) / 1000.0f;
                    reszecskek[i].vy = (rand() % 200) / 1000.0f;
                    reszecskek[i].vz = (rand() % 200 - 100.0f) / 1000.0f;
                    reszecskek[i].life = (rand() % 100) / 100.0f + 1.0f;
                }
            }
        }

        void drawReszecskek() {
            glPushMatrix();
            glTranslatef(0.0f, 0.5f, 0.0f);
            glBegin(GL_QUADS);
            for (int i = 0; i < RESZECSKESZAM; i++) {
                glColor4fv(reszecskek[i].color);
                glVertex3f(reszecskek[i].x - 0.1f, reszecskek[i].y - 0.1f, reszecskek[i].z);
                glVertex3f(reszecskek[i].x + 0.1f, reszecskek[i].y - 0.1f, reszecskek[i].z);
                glVertex3f(reszecskek[i].x + 0.1f, reszecskek[i].y + 0.1f, reszecskek[i].z);
                glVertex3f(reszecskek[i].x - 0.1f, reszecskek[i].y + 0.1f, reszecskek[i].z);
            }
            glEnd();
            glPopMatrix();
        }



*/













