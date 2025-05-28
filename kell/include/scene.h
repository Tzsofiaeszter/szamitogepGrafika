#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <model.h>

#include <stdbool.h>

typedef struct Scene{
    Model szoba;
    Model asztalka;
    Model szonyegke;
    Model csillarka;
    Model szek;
    Model konyvespolc;

    Material material;

    GLuint fal_texture_id;   // szoba
    GLuint fa2_texture_id;   // asztal
    GLuint fa0_texture_id;    // könyvespolc
    // GLuint fa3_texture_id;         //óra
    GLuint szek_texture_id;  // szék
    GLuint kek_texture_id;          //szőnyeg
    GLuint csillar_texture_id;// csillár


    GLuint help_texture;

    bool show_help;

    bool lighting_enabled;

    float light_intensity;

} Scene;


void init_scene(Scene* scene);
void set_lighting();
void set_material(const Material* material);
void update_scene(Scene* scene);
void render_scene(const Scene* scene);
//void draw_origin();
void render_help_overlay();

#endif 
