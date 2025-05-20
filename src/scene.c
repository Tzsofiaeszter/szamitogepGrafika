#include "scene.h"
#include "camera.h"
#include "load.h"
#include "model.h"
#include "init.h" 
#include"texture.h"
#include "draw.h"

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Globális változók

Scene scene;

// Inicializálás

void init_lights(Scene* scene) {
    scene->n_fenyek = 4;

// Fényforrás 0. = 1
    scene->fenyek[0].id = GL_LIGHT0;
    scene->fenyek[0].position[0] = 2.0f;
    scene->fenyek[0].position[1] = 5.0f;
    scene->fenyek[0].position[2] = 3.0f;
    scene->fenyek[0].position[3] = 1.0f; // Pontszerű fényforrás
    scene->fenyek[0].ambient[0] = 0.2f;
    scene->fenyek[0].ambient[1] = 0.2f;
    scene->fenyek[0].ambient[2] = 0.2f;
    scene->fenyek[0].ambient[3] = 1.0f;
    scene->fenyek[0].diffuse[0] = 0.8f;
    scene->fenyek[0].diffuse[1] = 0.8f;
    scene->fenyek[0].diffuse[2] = 0.8f;
    scene->fenyek[0].diffuse[3] = 1.0f;
    scene->fenyek[0].specular[0] = 0.5f;
    scene->fenyek[0].specular[1] = 0.5f;
    scene->fenyek[0].specular[2] = 0.5f;
    scene->fenyek[0].specular[3] = 1.0f;
    init_light(&scene->fenyek[0]);

// Fényforrás 1
    scene->fenyek[1].id = GL_LIGHT1;
    scene->fenyek[1].position[0] = -2.0f;
    scene->fenyek[1].position[1] = 2.0f;
    scene->fenyek[1].position[2] = -2.0f;
    scene->fenyek[1].position[3] = 1.0f;
    scene->fenyek[1].ambient[0] = 0.1f;
    scene->fenyek[1].ambient[1] = 0.1f;
    scene->fenyek[1].ambient[2] = 0.1f;
    scene->fenyek[1].ambient[3] = 1.0f;
    scene->fenyek[1].diffuse[0] = 0.6f;
    scene->fenyek[1].diffuse[1] = 0.6f;
    scene->fenyek[1].diffuse[2] = 0.6f;
    scene->fenyek[1].diffuse[3] = 1.0f;
    scene->fenyek[1].specular[0] = 0.3f;
    scene->fenyek[1].specular[1] = 0.3f;
    scene->fenyek[1].specular[2] = 0.3f;
    scene->fenyek[1].specular[3] = 1.0f;
    init_light(&scene->fenyek[1]);

// Fényforrás 2
    scene->fenyek[2].id = GL_LIGHT2;
    scene->fenyek[2].position[0] = 0.0f;
    scene->fenyek[2].position[1] = 4.0f;
    scene->fenyek[2].position[2] = 0.0f;
    scene->fenyek[2].position[3] = 1.0f;
    scene->fenyek[2].ambient[0] = 0.1f;
    scene->fenyek[2].ambient[1] = 0.1f;
    scene->fenyek[2].ambient[2] = 0.1f;
    scene->fenyek[2].ambient[3] = 1.0f;
    scene->fenyek[2].diffuse[0] = 0.5f;
    scene->fenyek[2].diffuse[1] = 0.5f;
    scene->fenyek[2].diffuse[2] = 0.5f;
    scene->fenyek[2].diffuse[3] = 1.0f;
    scene->fenyek[2].specular[0] = 0.2f;
    scene->fenyek[2].specular[1] = 0.2f;
    scene->fenyek[2].specular[2] = 0.2f;
    scene->fenyek[2].specular[3] = 1.0f;
    init_light(&scene->fenyek[2]);

// Fényforrás 3
    scene->fenyek[3].id = GL_LIGHT3;
    scene->fenyek[3].position[0] = 3.0f;
    scene->fenyek[3].position[1] = 3.0f;
    scene->fenyek[3].position[2] = -3.0f;
    scene->fenyek[3].position[3] = 1.0f;
    scene->fenyek[3].ambient[0] = 0.1f;
    scene->fenyek[3].ambient[1] = 0.1f;
    scene->fenyek[3].ambient[2] = 0.1f;
    scene->fenyek[3].ambient[3] = 1.0f;
    scene->fenyek[3].diffuse[0] = 0.7f;
    scene->fenyek[3].diffuse[1] = 0.7f;
    scene->fenyek[3].diffuse[2] = 0.7f;
    scene->fenyek[3].diffuse[3] = 1.0f;
    scene->fenyek[3].specular[0] = 0.4f;
    scene->fenyek[3].specular[1] = 0.4f;
    scene->fenyek[3].specular[2] = 0.4f;
    scene->fenyek[3].specular[3] = 1.0f;
    init_light(&scene->fenyek[3]);
}

void init_scene(Scene* scene){
// AJTO 4db
    load_model(&(scene->ajtofelfa1), "assets/models/ajtofelfa1.obj");
    load_model(&(scene->ajtolap1), "assets/models/ ajtolap1.obj");
    load_model(&(scene->ajtofelfa2), "assets/models/ajtofelfa2.obj");
    load_model(&(scene->ajtolap2), "assets/models/ajtolap2.obj");
    load_model(&(scene->ajtofelfa3), "assets/models/ajtofelfa3.obj");
    load_model(&(scene->ajtolap3), "assets/models/ajtolap3.obj");
    load_model(&(scene->ajtofelfa4), "assets/models/ajtofelfa4.obj");
    load_model(&(scene->ajtolap4), "assets/models/ajtolap4.obj");
// ASZTAL
    load_model(&(scene->asztal_lap), "assets/models/asztal_lap.obj");
    load_model(&(scene->asztal_lab), "assets/models/asztal_lab.obj");
// SZŐNYEG - ELŐSZOBÁBA
    load_model(&(scene->eloszoba_szonyeg), "assets/models/eloszoba_szonyeg.obj");
// FALAK
    load_model(&(scene->falak), "assets/models/falak.obj");
// KANAPÉ- NAPPALIBA
    load_model(&(scene->kanape), "assets/models/kanape.obj");
// KÉK PUFF- ELŐSZOBA
    load_model(&(scene->kek_pufika), "assets/models/kek_pufika.obj");
// KÜLTÉRI SZÉK
    load_model(&(scene->kintiSzek), "assets/models/kintiSzek.obj");
// KÜLTÉRI FA KORLÁT
    load_model(&(scene->kulteri_fa), "assets/models/kulteri_fa.obj");
// KÖNYVESPOLC KÖNYVEKKEL
    load_model(&(scene->konyvespolc), "assets/models/konyvespolc.obj");
//NAPPALI SZŐNYEGE
    load_model(&(scene->nappali_szonyeg), "assets/models/nappali_szonyeg.obj");
// KÜLTÉRI LÉPCSŐ ÉS PADLÓ
    load_model(&(scene->lepcso_padlo), "assets/models/lepcso_padlo.obj");
// BELTÉRI PARKETTA
   load_model(&(scene->padlo), "assets/models/padlo.obj");
// RÉGO ÓRA
    load_model(&(scene->regi_ora), "assets/models/regi_ora.obj");
// SZÉKEK AZ ELŐSZOBÁBA
    load_model(&(scene->szek_alj), "assets/models/szek_alj.obj");
    load_model(&(scene->szek_teteje), "assets/models/szek_teteje.obj");
// TETŐ 
    load_model(&(scene->teto), "assets/models/teto.obj");
 
// Textúrák betöltése
    load_textures(scene);

// Textúrák hozzárendelése a modellekhez
    scene->teto.material.texture_id = scene->texture_cserep;
    
    scene->asztal_lap.material.texture_id = scene->texture_fa2;
    scene->asztal_lab.material.texture_id = scene->texture_barna2;
    
    scene->kintiSzek.material.texture_id = scene->texture_barna;
    
    scene->ajtofelfa1.material.texture_id = scene->texture_fa1;
    scene->ajtolap1.material.texture_id = scene->texture_ajto;
    scene->ajtofelfa2.material.texture_id = scene->texture_fa1;
    scene->ajtolap2.material.texture_id = scene->texture_ajto;
    scene->ajtofelfa3.material.texture_id = scene->texture_fa1;
    scene->ajtolap3.material.texture_id = scene->texture_ajto;
    scene->ajtofelfa4.material.texture_id = scene->texture_fa1;
    scene->ajtolap4.material.texture_id = scene->texture_ajto;
   
    scene->konyvespolc.material.texture_id = scene->texture_barna2;
    
    scene->falak.material.texture_id = scene->texture_fal;
    
    scene->eloszoba_szonyeg.material.texture_id = scene->texture_fem;
    
    scene->nappali_szonyeg.material.texture_id = scene->texture_szonyeg;
    
    scene->lepcso_padlo.material.texture_id = scene->texture_barna;
    
    scene->padlo.material.texture_id = scene->texture_barna2; 
    
    scene->szek_alj.material.texture_id = scene->texture_fem;
    scene->szek_teteje.material.texture_id = scene->texture_szek;
    
    scene->kulteri_fa.material.texture_id = scene->texture_barna; 
    
    scene->regi_ora.material.texture_id = scene->texture_fa1; 

// Modellek alapértelmezett transzformációinak beállítása 
    scene->ajtofelfa1_transform.pozicio = (Vec3){-2.0f, 0.0f, 2.0f};
    scene->ajtofelfa1_transform.forgatas = (Vec3){0.0f, 90.0f, 0.0f};
    scene->ajtofelfa1_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};
    scene->ajtolap1_transform.pozicio = (Vec3){-2.0f, 0.0f, 2.0f};
    scene->ajtolap1_transform.forgatas = (Vec3){0.0f, 90.0f, 0.0f};
    scene->ajtolap1_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};
    scene->ajtofelfa2_transform.pozicio = (Vec3){2.0f, 0.0f, 2.0f};
    scene->ajtofelfa2_transform.forgatas = (Vec3){0.0f, 90.0f, 0.0f};
    scene->ajtofelfa2_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};
    scene->ajtolap2_transform.pozicio = (Vec3){2.0f, 0.0f, 2.0f};
    scene->ajtolap2_transform.forgatas = (Vec3){0.0f, 90.0f, 0.0f};
    scene->ajtolap2_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};
    scene->ajtofelfa3_transform.pozicio = (Vec3){-2.0f, 0.0f, -2.0f};
    scene->ajtofelfa3_transform.forgatas = (Vec3){0.0f, -90.0f, 0.0f};
    scene->ajtofelfa3_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};
    scene->ajtolap3_transform.pozicio = (Vec3){-2.0f, 0.0f, -2.0f};
    scene->ajtolap3_transform.forgatas = (Vec3){0.0f, -90.0f, 0.0f};
    scene->ajtolap3_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};
    scene->ajtofelfa4_transform.pozicio = (Vec3){2.0f, 0.0f, -2.0f};
    scene->ajtofelfa4_transform.forgatas = (Vec3){0.0f, -90.0f, 0.0f};
    scene->ajtofelfa4_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};
    scene->ajtolap4_transform.pozicio = (Vec3){2.0f, 0.0f, -2.0f};
    scene->ajtolap4_transform.forgatas = (Vec3){0.0f, -90.0f, 0.0f};
    scene->ajtolap4_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};
    scene->asztal_lap_transform.pozicio = (Vec3){0.0f, 0.5f, -1.5f}; 
    scene->asztal_lap_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->asztal_lap_transform.skalazas = (Vec3){2.0f, 1.0f, 1.0f}; 

    scene->asztal_lab_transform.pozicio = (Vec3){0.0f, 0.0f, -1.5f}; 
    scene->asztal_lab_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->asztal_lab_transform.skalazas = (Vec3){2.0f, 1.0f, 1.0f}; 

    scene->eloszoba_szonyeg_transform.pozicio = (Vec3){0.0f, 0.01f, 3.0f}; 
    scene->eloszoba_szonyeg_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->eloszoba_szonyeg_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};

    scene->falak_transform.pozicio = (Vec3){0.0f, 0.0f, 0.0f};
    scene->falak_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->falak_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};

    scene->kanape_transform.pozicio = (Vec3){1.0f, 0.3f, -2.0f};  
    scene->kanape_transform.forgatas = (Vec3){0.0f, 180.0f, 0.0f};
    scene->kanape_transform.skalazas = (Vec3){1.5f, 1.0f, 1.0f};

    scene->kek_pufika_transform.pozicio = (Vec3){-1.5f, 0.15f, 2.5f}; 
    scene->kek_pufika_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->kek_pufika_transform.skalazas = (Vec3){0.8f, 0.8f, 0.8f};

    scene->kintiSzek_transform.pozicio = (Vec3){-4.0f, 0.0f, -4.0f};
    scene->kintiSzek_transform.forgatas = (Vec3){0.0f, 45.0f, 0.0f};
    scene->kintiSzek_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};

    scene->kulteri_fa_transform.pozicio = (Vec3){-3.0f, 0.0f, -3.0f};
    scene->kulteri_fa_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->kulteri_fa_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};

    scene->konyvespolc_transform.pozicio = (Vec3){2.5f, 0.0f, 1.5f};
    scene->konyvespolc_transform.forgatas = (Vec3){0.0f, -90.0f, 0.0f};
    scene->konyvespolc_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};

    scene->nappali_szonyeg_transform.pozicio = (Vec3){0.0f, 0.01f, -1.5f};
    scene->nappali_szonyeg_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->nappali_szonyeg_transform.skalazas = (Vec3){2.5f, 0.1f, 2.5f};

    scene->lepcso_padlo_transform.pozicio = (Vec3){-4.0f, 0.0f, 4.0f};
    scene->lepcso_padlo_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->lepcso_padlo_transform.skalazas = (Vec3){1.0f, 1.0f, 1.0f};

    scene->padlo_transform.pozicio = (Vec3){0.0f, 0.0f, 0.0f};
    scene->padlo_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->padlo_transform.skalazas = (Vec3){5.0f, 0.1f, 5.0f};

    scene->regi_ora_transform.pozicio = (Vec3){2.0f, 1.0f, 2.8f};
    scene->regi_ora_transform.forgatas = (Vec3){0.0f, 180.0f, 0.0f};
    scene->regi_ora_transform.skalazas = (Vec3){0.5f, 0.5f, 0.5f};

    scene->szek_alj_transform.pozicio = (Vec3){-1.5f, 0.0f, 1.5f};
    scene->szek_alj_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->szek_alj_transform.skalazas = (Vec3){0.7f, 0.7f, 0.7f};

    scene->szek_teteje_transform.pozicio = (Vec3){-1.5f, 0.5f, 1.5f};
    scene->szek_teteje_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->szek_teteje_transform.skalazas = (Vec3){0.7f, 0.7f, 0.7f};

    scene->teto_transform.pozicio = (Vec3){0.0f, 4.0f, 0.0f};
    scene->teto_transform.forgatas = (Vec3){0.0f, 0.0f, 0.0f};
    scene->teto_transform.skalazas = (Vec3){5.0f, 0.1f, 5.0f};

}

void load_textures(Scene* scene) {
// tetőhöz
    scene->texture_cserep = load_texture("assets/textures/cserep.png");
// asztal, kültéri szék
    scene->texture_fa1 = load_texture("assets/textures/faHatas1.png");
// könyvespolc, ajtófélfa
    scene->texture_fa2 = load_texture("assets/textures/faHatas2.png");
// falakhoz kívülre
    scene->texture_fal = load_texture("assets/textures/fal.png");
// szőnyeg az előszobában
    scene->texture_fem = load_texture("assets/textures/fem.png");
// szőnyeg a nappaliban
    scene->texture_szonyeg = load_texture("assets/textures/szonyeg.png");
//kinti korlát
    scene->texture_barna = load_texture("assets/textures/barna.png");
//székeknek
    scene->texture_szek = load_texture("assets/textures/szek.png");
//ajtónak
    scene->texture_ajto = load_texture("assets/textures/ajto.png");
// beltéri járólap
    scene->texture_barna2 = load_texture("assets/textures/barna2.png");
}

void set_material(const Material* material) {
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material->shininess); 
}

void set_lighting(){
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void update_scene(Scene* scene){
    // Ha nincs frissítés, üres maradhat - animációkhoz
}

void set_scene_lights(const Scene* scene){
    if (scene->n_fenyek > 0) {
        for (int i = 0; i < scene->n_fenyek; ++i) {
            glLightfv(scene->fenyek[i].id, GL_AMBIENT, scene->fenyek[i].ambient);
            glLightfv(scene->fenyek[i].id, GL_DIFFUSE, scene->fenyek[i].diffuse);
            glLightfv(scene->fenyek[i].id, GL_SPECULAR, scene->fenyek[i].specular);
            glLightfv(scene->fenyek[i].id, GL_POSITION, scene->fenyek[i].position);
        }
    }
}


void draw_single_model(const Model* model) {
    if (model && model->triangles && model->vertices) {
        glBindTexture(GL_TEXTURE_2D, model->material.texture_id);
        glBegin(GL_TRIANGLES);

        for (int i = 0; i < model->n_triangles; ++i) {
            for (int j = 0; j < 3; ++j) {
                FacePoint point = model->triangles[i].points[j];

                // Textúra koordináták
                if (point.texture_index > 0 && model->texture_vertices) {
                    TextureVertex tex = model->texture_vertices[point.texture_index];
                    glTexCoord2f(tex.u, tex.v);
                }

                // Normál vektor
                if (point.normal_index > 0 && model->normals) {
                    Vertex norm = model->normals[point.normal_index];
                    glNormal3f(norm.x, norm.y, norm.z);
                }

                // Vertex koordináták
                if (point.vertex_index > 0 && model->vertices) {
                    Vertex v = model->vertices[point.vertex_index];
                    glVertex3f(v.x, v.y, v.z);
                }
            }
        }

        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


void render_scene(const Scene* scene){
    set_material(&(scene->material)); 
    set_lighting();

    set_lighting();

// Padló kirajzolása
    glPushMatrix();
    draw_model(&(scene->padlo));
    glPopMatrix();

// Falak kirajzolása
    glPushMatrix();
    draw_model(&(scene->falak));
    glPopMatrix();

// Tető
    glPushMatrix();
    draw_model(&(scene->teto));
    glPopMatrix();

// Asztal
    glPushMatrix();
    draw_model(&(scene->asztal_lap));
    glPopMatrix();

    glPushMatrix();
    draw_model(&(scene->asztal_lab));
    glPopMatrix();

// Szőnyeg az előszobában
    glPushMatrix();
    draw_model(&(scene->eloszoba_szonyeg));
    glPopMatrix();

// Kanapé
    glPushMatrix();
    draw_model(&(scene->kanape));
    glPopMatrix();

// Kék puff
    glPushMatrix();
    draw_model(&(scene->kek_pufika));
    glPopMatrix();

// Kültéri szék
    glPushMatrix();
    draw_model(&(scene->kintiSzek));
    glPopMatrix();

// Kültéri fa korlát
    glPushMatrix();
    draw_model(&(scene->kulteri_fa));
    glPopMatrix();

// Könyvespolc
    glPushMatrix();
    draw_model(&(scene->konyvespolc));
    glPopMatrix();

// Nappali szőnyeg
    draw_model(&(scene->nappali_szonyeg));
    glPopMatrix();

// Kültéri lépcső és padló
    glPushMatrix();
    draw_model(&(scene->lepcso_padlo));
    glPopMatrix();

// Régi óra
    glPushMatrix();
    draw_model(&(scene->regi_ora));
    glPopMatrix();

// Székek az előszobában
    glPushMatrix();
    draw_model(&(scene->szek_alj));
    glPopMatrix();

    glPushMatrix();
    draw_model(&(scene->szek_teteje));
    glPopMatrix();

// Ajtók
    glPushMatrix();
    draw_model(&(scene->ajtofelfa1));
    glPopMatrix();

    glPushMatrix();
    draw_model(&(scene->ajtolap1));
    glPopMatrix();

    glPushMatrix();
    draw_model(&(scene->ajtofelfa2));
    glPopMatrix();

    glPushMatrix();
    draw_model(&(scene->ajtolap2));
    glPopMatrix();

    glPushMatrix();
    draw_model(&(scene->ajtofelfa3));
    glPopMatrix();

    glPushMatrix();
    draw_model(&(scene->ajtolap3));
    glPopMatrix();

    glPushMatrix();
    draw_model(&(scene->ajtofelfa4));
    glPopMatrix();

    glPushMatrix();
    draw_model(&(scene->ajtolap4));
    glPopMatrix();

    /*
    glPushMatrix();
    draw_model(&(draw_gradient_background()));
    glPopMatrix();
    */

}

//draw_model(const Model* model);
/*void handle_resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}*/


/*
void draw_gradient_background(){
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPT_TEST);

    glMatrixMode(GL_PROJECTION);
    GLPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1 );

    glMatrixMode(GL_MODELVIEW);
    GLPushMatrix();
    glLoadIdentity();

    glbegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.6f); // sötétkék
    glVertex2f(0.0f , 1.0f);
    glVertex2f(0.0f , 0.0f); // x és y pontkat várja

    glColor3f(0.4f, 0.3f, 0.5f); // világosabb kék
    glVertex2f(0.0f , 0.0f);
    glVertex2f(1.0f , 0.0f); // x és y pontkat várja

    glColor3f(0.25f, 0.2f, 0.55f); // közepesen sötét kék
    glVertex2f(1.0f , 0.0f);
    glVertex2f(0.0f , 1.0f); // x és y pontkat várja

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMod3e(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTNING);
}
    */

    //void cleanup();