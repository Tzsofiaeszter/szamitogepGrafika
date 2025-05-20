#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "load.h"
#include "model.h"
#include "draw.h"
#include "texture.h"
#include "init.h"
#include "light.h"

typedef struct{
    Model ajtofelfa1;
    Model ajtofelfa2;
    Model ajtofelfa3;
    Model ajtofelfa4;
    Model ajtolap1;
    Model ajtolap2;
    Model ajtolap3;
    Model ajtolap4;        
    Model asztal_lab;
    Model asztal_lap;   
    Model eloszoba_szonyeg;
    Model falak;
    Model kanape;
    Model kek_pufika;
    Model konyvespolc;
    Model kintiSzek;
    Model kulteri_fa;
    Model lepcso_padlo;
    Model nappali_szonyeg;
    Model padlo;    
    Model regi_ora;
    Model szek_alj;
    Model szek_teteje;
    Model teto;

    Material material;
    
    GLuint texture_ajto;
    GLuint texture_barna;
    GLuint texture_barna2;
    GLuint texture_cserep;
    GLuint texture_fa1;
    GLuint texture_fa2;
    GLuint texture_fal;
    GLuint texture_fem;
    GLuint texture_szek;
    GLuint texture_szonyeg;
   

    // Modell pozíciók, forgatások, skálázások
    Transform ajtofelfa1_transform;
    Transform ajtolap1_transform;
    Transform ajtofelfa2_transform;
    Transform ajtolap2_transform;
    Transform ajtofelfa3_transform;
    Transform ajtolap3_transform;
    Transform ajtofelfa4_transform;
    Transform ajtolap4_transform;
    Transform asztal_lap_transform;
    Transform asztal_lab_transform;
    Transform eloszoba_szonyeg_transform;
    Transform falak_transform;
    Transform kanape_transform;
    Transform kek_pufika_transform;
    Transform kintiSzek_transform;
    Transform kulteri_fa_transform;
    Transform konyvespolc_transform;
    Transform nappali_szonyeg_transform;
    Transform lepcso_padlo_transform;
    Transform padlo_transform;
    Transform regi_ora_transform;
    Transform szek_alj_transform;
    Transform szek_teteje_transform;
    Transform teto_transform;

    Camera camera;
    Light fenyek[4]; // pl.: 4 fényforrás
    int n_fenyek;

} Scene;

int init();
void init_camera(Camera* camera);
void init_light(Light* light);
void init_lights(Scene* scene); 
void init_scene(Scene* scene);
void load_textures(Scene* scene); 
void set_material(const Material* material); 
void set_lighting();
void set_scene_lights(const Scene* scene);
void update_scene(Scene* scene);
void draw_model(const Model* model);
void draw_single_model(const Model* model);
void render_scene(const Scene* scene);
//void handle_resize(int w, int h); 
/*
void draw_gradient_background(){
  */
void cleanup(); 

#endif 