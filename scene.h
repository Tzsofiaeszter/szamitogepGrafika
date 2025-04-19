#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model asztal;
    Model szek1;
    Model szek2;
    Model szek3;
    Model szek4;
    Model szek5;
    Model szek6;
    Model kandallo;
    Model ingaora;
    Model konyvespolc;

    Material material;
    GLuint texture_id;
    
} Scene;


void init_scene(Scene* scene);

void set_lighting();

void set_material(const Material* material);

void update_scene(Scene* scene);

void render_scene(const Scene* scene);

void draw_origin();

#endif /* SCENE_H */

