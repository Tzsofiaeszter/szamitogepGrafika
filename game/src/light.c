#include "light.h" 

#include <string.h>
#include <GL/gl.h>

void init_light(Light* light) {
    if (!light) return;

    GLfloat zero[4] = {0.0f, 0.0f, 0.0f, 0.0f};

  // Alapértékek, ha az adott komponens teljesen nullás
    if (memcmp(light->ambient, zero, sizeof(zero)) == 0) {
        GLfloat default_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
        memcpy(light->ambient, default_ambient, sizeof(default_ambient));
    }

    if (memcmp(light->diffuse, zero, sizeof(zero)) == 0) {
        GLfloat default_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
        memcpy(light->diffuse, default_diffuse, sizeof(default_diffuse));
    }

    if (memcmp(light->specular, zero, sizeof(zero)) == 0) {
        GLfloat default_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        memcpy(light->specular, default_specular, sizeof(default_specular));
    }

      // OpenGL fény beállítása
    glEnable(light->id); // pl. GL_LIGHT0
    glLightfv(light->id, GL_POSITION, light->position);
    glLightfv(light->id, GL_AMBIENT,  light->ambient);
    glLightfv(light->id, GL_DIFFUSE,  light->diffuse);
    glLightfv(light->id, GL_SPECULAR, light->specular);
}

void set_light_brightness(Light* light, int brightness) {
    if (!light) return;

    GLfloat normalized = (GLfloat)brightness / 255.0f;
    GLfloat ambient[]  = {normalized, normalized, normalized, 1.0f};
    GLfloat diffuse[]  = {normalized, normalized, normalized, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f}; 

    glLightfv(light->id, GL_AMBIENT,  ambient);
    glLightfv(light->id, GL_DIFFUSE,  diffuse);
    glLightfv(light->id, GL_SPECULAR, specular);
}

void set_lighting(){
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}