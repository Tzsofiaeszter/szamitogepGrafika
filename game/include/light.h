#ifndef LIGHT_H
#define LIGHT_H

#include <GL/gl.h>

typedef struct Light {
    GLenum id;            //GL_LIGHT0
    GLfloat position[4];  // x,y,z,w=1
    GLfloat ambient[4];   // környezeti fény
    GLfloat diffuse[4];   // szórt fény színe
    GLfloat specular[4];  // visszaverődő fény színe
} Light;

void init_light(Light* light);
void set_light_brightness(Light* light, int brightness);
void set_lighting(void);

#endif 