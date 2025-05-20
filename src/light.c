// light.c

#include <GL/gl.h>
#include "light.h"  // amiben deklarálod a Light struct-ot és az init_light prototípust

void init_light(Light* light) {
    glEnable(light->id); // pl. GL_LIGHT0

    // Fény pozíció, színek a light structból
    glLightfv(light->id, GL_POSITION, light->position);
    glLightfv(light->id, GL_AMBIENT, light->ambient);
    glLightfv(light->id, GL_DIFFUSE, light->diffuse);
    glLightfv(light->id, GL_SPECULAR, light->specular);


// A fő programban egyszer kell bekapcsolni ezeket:
glEnable(GL_LIGHTING);
glEnable(GL_COLOR_MATERIAL);
glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}