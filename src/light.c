#include "light.h" 

#include <GL/gl.h>

void init_light(Light* light) {
    glEnable(light->id); // pl. GL_LIGHT0

    // Fény pozíció, színek a light structból
    glLightfv(light->id, GL_POSITION, light->position);
    glLightfv(light->id, GL_AMBIENT, light->ambient);
    glLightfv(light->id, GL_DIFFUSE, light->diffuse);
    glLightfv(light->id, GL_SPECULAR, light->specular);
}

// Fényforrás fényerejének beállítása
void set_light_brightness(Light* light, int brightness) {
    if (!light) return;

    // A fényerő 0 és 255 közötti értéket kap, amit 0.0f és 1.0f közé kell normalizálni
    GLfloat normalized_brightness = (GLfloat)brightness / 255.0f;

    // Csak az ambient és diffuse komponenseket állítjuk a fényerővel
    light->ambient[0] = normalized_brightness;
    light->ambient[1] = normalized_brightness;
    light->ambient[2] = normalized_brightness;
    // light->ambient[3] = 1.0f; // Az alpha értéket általában nem módosítjuk

    light->diffuse[0] = normalized_brightness;
    light->diffuse[1] = normalized_brightness;
    light->diffuse[2] = normalized_brightness;
    // light->diffuse[3] = 1.0f;

    // Alkalmazzuk a változásokat az OpenGL fényforrásra
    glLightfv(light->id, GL_AMBIENT, light->ambient);
    glLightfv(light->id, GL_DIFFUSE, light->diffuse);
}

// set_lighting függvény, ha globális fénybeállításokat végez
// Ezt a függvényt általában az OpenGL inicializálásakor hívják meg egyszer.
void set_lighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // Itt engedélyezhetők a specifikus fényforrások is, pl. glEnable(GL_LIGHT0);
}
