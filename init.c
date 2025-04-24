// grafikai inicializálás

#include "init.h"

void init() {
    glEnable(GL_DEPTH_TEST); // Engedélyezi a mélységi tesztet (fontos 3D grafikához)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Háttérszín beállítása: fekete
    glShadeModel(GL_FLAT); // Árnyékolás beállítása (lapos árnyékolás)

    // Fényforrás beállítása (itt feltételezve, hogy már deklarálva van egy 'light' változó)
    light.position[0] = 1.0f; // Fény X koordinátája
    light.position[1] = 1.0f; // Fény Y koordinátája
    light.position[2] = 1.0f; // Fény Z koordinátája
    light.position[3] = 1.0f; // w = 1, ha pontszerű fény (0, ha irányított fény)
    light.color[0] = 1.0f;    // Fény színének piros komponense
    light.color[1] = 1.0f;    // Fény színének zöld komponense
    light.color[2] = 1.0f;    // Fény színének kék komponense
    light.color[3] = 1.0f;    // Fény átlátszóságának beállítása
    light.intensity = 1.0f;   // Fényerő beállítása
    light.id = GL_LIGHT0;     // Az első fényforrás azonosítója

    initLight(&light);  // Fényforrás inicializálása OpenGL-ben
}
