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
    Model book1;
    Model book2;
    
    Material material;

    GLuint fal_texture_id;   // szoba
    GLuint fa2_texture_id;   // asztal
    GLuint fa0_texture_id;    // könyvespolc
    // GLuint fa3_texture_id;         //óra
    GLuint szek_texture_id;  // szék
    GLuint kek_texture_id;          //szőnyeg
    GLuint csillar_texture_id;// csillár
    GLuint book1_texture_id;
    GLuint book2_texture_id;

    GLuint help_texture_id;

    bool show_help_visible;

    bool lighting_enabled;

    float light_intensity;

    float szek1_position[3];
    float szek2_position[3];

} Scene;


void init_scene(Scene* scene);
void set_lighting();
void set_material(const Material* material);
void update_scene(Scene* scene);
void render_scene(const Scene* scene);
//void draw_origin();
void render_help_overlay();

void move_szek1(Scene* scene, float dx, float dy, float dz);
void move_szek2(Scene* scene, float dx, float dy, float dz);


#endif 
