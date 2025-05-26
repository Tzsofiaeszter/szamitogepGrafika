#ifndef SCENE_H
#define SCENE_H

#include "model.h"
#include "light.h"
#include "utils.h"
#include "camera.h"
#include <stdbool.h>

typedef struct Scene{
  Material material;
  Light light;
  
  Model szoba;
  Model ajtofelfa;
  Model ajtolap;
  Model asztal_lap;
  Model asztal_lab;
  Model szek_teteje;
  Model szek_alj;
  Model szonyeg;
  Model kek_pufika;
  Model kintiSzek;
  Model konyvespolc;
  Model regi_ora;
  Model tetoCsapott;
  Model books;
  Model csillar;

  GLuint ajtob_texture;
  GLuint ajto_texture;
  GLuint fa1_texture;
  GLuint fa2_texture;
  GLuint fa3_texture;
  GLuint fa4_texture;
  GLuint szek_texture;
  GLuint barna_texture;
  GLuint szonyeg_texture;
  GLuint kek_texture;
  GLuint fal_texture;
  GLuint cserep_texture;
  GLuint csillar_texture;
  GLuint book_texture;

  GLuint segedkepernyo_texture;
  GLuint eg_background_texture;

  bool help;
  float platform_scale_z;

} Scene;


void init_scene(Scene* scene);
void set_lighting();
void set_material(const Material* material);
void update_scene(Scene* scene);
void render_scene(const Scene* scene);
void toggle_ajto();

#endif 
