#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "utils.h"
#include <model.h>

#include <stdbool.h>

#define MAX_RAINDROPS 1000

typedef struct RainDrop {
    vec3 position;
    float speed;
} RainDrop;

typedef struct Scene{
    Model szoba;
    Model asztalka;
    Model szonyegke;
    Model csillarka;
    Model szek;
    Model konyvespolc;
    Model book1;
    Model book2;
    Model gyep;
    Model fa1;
   

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
    GLuint gyep_texture_id;
    GLuint facska1_texture_id;

    GLuint help_texture_id;

    //GLuint sky_top_texture_id;
    GLuint sky_side_texture_id;

    bool show_help_visible;

    bool lighting_enabled;

    float light_intensity;

    RainDrop raindrops[MAX_RAINDROPS];
    bool rain_enabled;

    vec3 szek1_position;
    vec3 szek2_position;

    
    bool lightning_active;
    float lightning_intensity;    // villanás fényereje (0..1)
    int lightning_timer;          // időzítő a villanás állapotához (pl. frame-ekben)
    int lightning_cooldown;       // idő a következő villanásig

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


void increase_light(Scene* scene);

void decrease_light(Scene* scene);


void draw_skybox(const Scene* scene, float size);

#endif 