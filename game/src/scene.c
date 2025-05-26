#include "scene.h"

#include "load.h"
#include "draw.h"
#include "utils.h"
#include "texture.h"
#include "light.h"
#include "transform.h"
#include "render.h"

#include <stdlib.h>
#include <stdbool.h>
#define _USE_MATH_DEFINES
#include <math.h> 

static float ajto_angle = 0.0f;
static bool ajto_nyitva = false;

void init_scene(Scene* scene){
    if (!scene) return;
//SZOBA
    load_model(&(scene->szoba), "assets/models/szoba.obj");
    if (scene->szoba.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az szoba.obj modellt!\n");
        //exit(1);
        }else {
                printf("szoba betoltve\n");
                scale_model(&(scene->szoba), 15.0, 20.0, 15.0);         // Szoba méretezése: 10 x 20 x 15
        }
//TETŐ
    load_model(&(scene->tetoCsapott), "assets/models/tetoCsapott.obj");
    if (scene->tetoCsapott.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az ajtofelfa.obj modellt!\n");
        //exit(1);
        }else {
                printf("teto betoltve\n");
                scale_model(&(scene->tetoCsapott), 15.0, 20.0, 4.0);   // Méretre állítás: 10 x 20 x 4
        }
//AJTÓ FÉLFA
    load_model(&(scene->ajtofelfa), "assets/models/ajtofelfa.obj");
            if (scene->ajtofelfa.vertices == NULL) {
            fprintf(stderr, "Hiba: Nem sikerult betolteni az ajtofelfa.obj modellt!\n");
            //exit(1);
            }else {
                printf("ajtofelfa betoltve\n");
                scale_model(&(scene->ajtofelfa), 5.0, 0.2, 15.0);
            }
//AJTÓ LAP
    load_model(&(scene->ajtolap), "assets/models/ajtolap.obj");
        if (scene->ajtolap.vertices == NULL) {
            fprintf(stderr, "Hiba: Nem sikerult betolteni az ajtolap.obj modellt!\n");
            //exit(1);
            }else {
                printf("ajtolap betoltve\n");
                scale_model(&(scene->ajtolap),  5.0, 0.2, 15.0);
            }
//ASZTAL LAP
load_model(&(scene->asztal_lap), "assets/models/asztal_lap.obj");
    if (scene->asztal_lap.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az asztal_lap.obj modellt!\n");
        //exit(1);
        }else {
            printf("asztalLap betoltve\n");
            scale_model(&(scene->asztal_lap), 4.0f, 2.0f, 0.3f);
        }
//ASZTAL LAB
load_model(&(scene->asztal_lab), "assets/models/asztal_lab.obj");
    if (scene->asztal_lab.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az asztal_lab.obj modellt!\n");
        //exit(1);
        }else {
            printf("asztalLab betoltve\n");
            scale_model(&(scene->asztal_lab), 1.5f, 1.5f, 1.0f);
        }
//SZÉK TETEJE
 load_model(&(scene->szek_teteje), "assets/models/szek_teteje.obj");
    if (scene->szek_teteje.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az szek-teteje.obj modellt!\n");
        //exit(1);
        }else {
            printf("szekTeteje betoltve\n");
            scale_model(&(scene->szek_teteje), 1.0f, 1.0f, 0.7f);

        }
//SZÉK ALJA            
     load_model(&(scene->szek_alj), "assets/models/szek_alj.obj");
    if (scene->szek_alj.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az szek_alj.obj modellt!\n");
        //exit(1);
        }else {
            printf("szekAlja betoltve\n");
            scale_model(&(scene->szek_alj), 1.0f, 1.0f, 0.5f);
        }
//SZŐNYEG        
     load_model(&(scene->szonyeg), "assets/models/szonyeg.obj");
    if (scene->szonyeg.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az szonyeg.obj modellt!\n");
       //exit(1);
        }else {
            printf("szonyeg betoltve\n");
            scale_model(&(scene->szonyeg), 19.0f, 14.0f, 0.02f);           // szoba méretéből 1-1 egységgel kisebb
        }
//PUFI
    load_model(&(scene->kek_pufika), "assets/models/kek_pufika.obj");
    if (scene->kek_pufika.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az kek_pufika.obj modellt!\n");
        //xit(1);
        }else {
            printf("pufika betoltve\n");
            scale_model(&(scene->kek_pufika), 4.0f, 2.0f, 2.5f); 
        }
        
    load_model(&(scene->kintiSzek), "assets/models/kintiSzek.obj");
    if (scene->kintiSzek.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az kintiSzek.obj modellt!\n");
        //exit(1);
        }else {
            printf("kintiSzek betoltve\n");
            scale_model(&(scene->kintiSzek), 5.0f, 2.0f, 3.0f); 
        }
            
    load_model(&(scene->konyvespolc), "assets/models/konyvespolc.obj");
    if (scene->konyvespolc.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az konyvespolc.obj modellt!\n");
        //exit(1);
        }else {
            printf("konyvespolc betoltve\n");
            scale_model(&(scene->konyvespolc), 5.0f, 3.0f, 10.0f); 
        }
        
    load_model(&(scene->books), "assets/models/books.obj");
    if (scene->books.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az books.obj modellt!\n");
        //exit(1);
        }else {
            printf("books betoltve\n");
            scale_model(&(scene->books), 1.0f, 1.0f, 0.2f); 

        }
        
    load_model(&(scene->regi_ora), "assets/models/regi_ora.obj");
    if (scene->regi_ora.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az regi_ora.obj modellt!\n");
        //exit(1);
        }else {
            printf("regiOra betoltve\n");
            scale_model(&(scene->regi_ora), 2.0f, 3.0f, 0.02f); 

        }
        
    load_model(&(scene->csillar), "assets/models/csillar.obj");
    if (scene->csillar.vertices == NULL) {
        fprintf(stderr, "Hiba: Nem sikerult betolteni az csillar.obj modellt!\n");
        //exit(1);
        }else {
            printf("csillar betoltve\n");
            scale_model(&(scene->csillar), 2.5f, 2.5f, 0.02f); 

        }
        
   
        


    scene->ajto_texture = load_texture("assets/textures/ajto.png");
            if (scene->ajto_texture == 0) {
            fprintf(stderr, "Hiba:ajto textúra betöltése sikertelen.\n");
            //exit(1);
            } else {
                printf("ajto.png betoltve\n");
            }

    scene->ajtob_texture = load_texture("assets/textures/ajtob.png");
        if (scene->ajtob_texture == 0) {
            fprintf(stderr, "Hiba:ajtob textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("ajtob.png betoltve\n");
            }

    scene->fa1_texture = load_texture("assets/textures/fa1.png");
        if (scene->fa1_texture == 0) {
            fprintf(stderr, "Hiba:fa1 textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("fa1.png betoltve\n");
            }

    scene->fa2_texture = load_texture("assets/textures/fa2.png");
        if (scene->fa2_texture == 0) {
            fprintf(stderr, "Hiba:fa2 textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("fa2.png betoltve\n");
            }

    scene->fa3_texture = load_texture("assets/textures/fa3.png");
        if (scene->fa3_texture == 0) {
            fprintf(stderr, "Hiba:fa3 textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
               printf("fa3.png betoltve\n");
            }

    scene->fa4_texture = load_texture("assets/textures/fa4.png");
        if (scene->fa4_texture == 0) {
            fprintf(stderr, "Hiba:fa4 textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("fa4.png betoltve\n");
            }

    scene->szek_texture = load_texture("assets/textures/szek.png");
        if (scene->szek_texture == 0) {
            fprintf(stderr, "Hiba:szek textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("szek.png betoltve\n");
            }

    scene->barna_texture = load_texture("assets/textures/barna.png");
        if (scene->barna_texture == 0) {
            fprintf(stderr, "Hiba:barna textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("barna.png betoltve\n");
            }

    scene->szonyeg_texture = load_texture("assets/textures/szonyeg.png");
        if (scene->szonyeg_texture == 0) {
            fprintf(stderr, "Hiba:szonyeg textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("szonyeg.png betoltve\n");
            }
    
    scene->fal_texture = load_texture("assets/textures/fal.png");
        if (scene->fal_texture == 0) {
            fprintf(stderr, "Hiba:FAL textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("FAL.png betoltve\n");
            }

    scene->kek_texture = load_texture("assets/textures/kek.png");
        if (scene->kek_texture == 0) {
            fprintf(stderr, "Hiba:kek textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("kek.png betoltve\n");
            }
    
    scene->cserep_texture = load_texture("assets/textures/cserep.png");
        if (scene->cserep_texture == 0) {
            fprintf(stderr, "Hiba:cserep textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("cserep.png betoltve\n");
            }
    
    scene->book_texture = load_texture("assets/textures/book.png");
        if (scene->book_texture == 0) {
            fprintf(stderr, "Hiba:book textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("book.png betoltve\n");
            }
  
    scene->csillar_texture = load_texture("assets/textures/csillar.png");
        if (scene->csillar_texture == 0) {
            fprintf(stderr, "Hiba:csillar textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("csillar.png betoltve\n");
            }
  
    scene->segedkepernyo_texture = load_texture("assets/textures/helpp.png");
        if (scene->segedkepernyo_texture == 0) {
            fprintf(stderr, "Hiba:help textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("helpp.png betoltve\n");
            }

    scene->eg_background_texture = load_texture("assets/textures/eg.png");
        if (scene->eg_background_texture == 0) {
            fprintf(stderr, "Hiba:eg textúra betöltése sikertelen.\n");
            //exit(1);
            }else {
                printf("eg.png betoltve\n");
            }  

    glEnable(GL_TEXTURE_2D);

    /*scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
*/

    scene->material.ambient = (Color){0.2f, 0.2f, 0.2f};
    scene->material.diffuse = (Color){0.8f, 0.8f, 0.8f};
    scene->material.specular = (Color){1.0f, 1.0f, 1.0f};
    scene->material.shininess = 50.0f;

    scene->light = (Light){
        .id = GL_LIGHT0,
        .position = {1.0f, 1.0f, 1.0f, 1.0f},
        .ambient = {0.2f, 0.2f, 0.2f, 1.0f},
        .diffuse = {0.7f, 0.7f, 0.7f, 1.0f},
        .specular = {1.0f, 1.0f, 1.0f, 1.0f}
    };

    init_light(&scene->light);
        printf("init_light() lefutott\n");
    set_light_brightness(&scene->light, 180);
        printf("set_light_brightness() lefutott\n");

    printf("init_scene() sikeresen lefutott\n");

    }

void set_material(const Material* material){
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

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene){
    (void)scene;
}

void render_scene(const Scene* scene)
{
// Alap beállítások
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    set_material(&scene->material);
    set_lighting();

// Szoba
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); 
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, scene->fal_texture);
    draw_model(&scene->szoba);
    glPopMatrix();
// Tető
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 15.0f);  // A szoba tetején
    glBindTexture(GL_TEXTURE_2D, scene->cserep_texture);
    draw_model(&scene->tetoCsapott);
    glPopMatrix();

// Ajtó félfa
    glPushMatrix();
    glTranslatef(7.5f, -10.0f, 0.0f);  // jobb széle a szobának
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);  // Az ajtó jobbra nézzen
    glBindTexture(GL_TEXTURE_2D, scene->ajtob_texture);
    draw_model(&scene->ajtofelfa);
    glPopMatrix();

// Ajtó lap
    glPushMatrix();
    glTranslatef(7.5f, -10.0f, 0.0f);  // Ugyanoda mint a félfa
    glRotatef(ajto_angle, 0.0f, 0.0f, 1.0f);  // Ajtó nyitása
    glBindTexture(GL_TEXTURE_2D, scene->ajto_texture);
    draw_model(&scene->ajtolap);
    glPopMatrix();

// Asztal lap
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); // Középen
    glBindTexture(GL_TEXTURE_2D, scene->fa2_texture);
    draw_model(&scene->asztal_lap);
    glPopMatrix();

// Asztal láb
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.5f); // Asztalláb lejjebb
    glBindTexture(GL_TEXTURE_2D, scene->fa2_texture);
    draw_model(&scene->asztal_lab);
    glPopMatrix();

// Székek (6 db körben)
    float radius = 3.5f;
    for (int i = 0; i < 6; i++) {
        float angle = i * 60.0f * (M_PI / 180.0f);
        float x = radius * cos(angle);
        float y = radius * sin(angle);

    // Szék alja
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
        glRotatef(-i * 60.0f, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, scene->barna_texture);
        draw_model(&scene->szek_alj);
        glPopMatrix();

    // Szék teteje
        glPushMatrix();
        glTranslatef(x, y, 0.5f);
        glRotatef(-i * 60.0f, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, scene->szek_texture);
        draw_model(&scene->szek_teteje);
        glPopMatrix();
    }

// Szőnyeg
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.01f);  // A padlóra, picit megemelve
    glBindTexture(GL_TEXTURE_2D, scene->szonyeg_texture);
    draw_model(&scene->szonyeg);
    glPopMatrix();

// Kek pufika
    glPushMatrix();
    glTranslatef(-5.5f, 5.5f, 0.0f);  // Könyvespolc mellett
    glBindTexture(GL_TEXTURE_2D, scene->kek_texture);
    draw_model(&scene->kek_pufika);
    glPopMatrix();

// Kinti szék - a bejárattal szemközti fal előtt, kívül
    glPushMatrix();
    glTranslatef(0.0f, 10.5f, 0.0f); // Fal elé tesszük Y irányban
    glBindTexture(GL_TEXTURE_2D, scene->fa4_texture);
    draw_model(&scene->kintiSzek);
    glPopMatrix();;

// Könyvespolc
    glPushMatrix();
    glTranslatef(-7.5f, 7.5f, 0.0f);  // 
    glBindTexture(GL_TEXTURE_2D, scene->fa1_texture);
    draw_model(&scene->konyvespolc);
    glPopMatrix();

// Könyvek a polcon
    glPushMatrix();
    glTranslatef(-7.5f, 7.5f, 0.2f);  // Ugyanaz a pozíció, de kicsit kijjebb a Z-tengely mentén
    glBindTexture(GL_TEXTURE_2D, scene->book_texture);
    draw_model(&scene->books);
    glPopMatrix();


// Régi óra
    glPushMatrix();
    glTranslatef(0.0f, 9.9f, 5.0f);  // X = 0 (középre), Y = 9.9 (a fal előtt), Z = 5 (magasság)
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);  // Ha háttal lenne, megfordítás
    glBindTexture(GL_TEXTURE_2D, scene->fa3_texture);
    draw_model(&scene->regi_ora);
    glPopMatrix();

// Csillár
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 13.5f); // Lefelé lóg 1.5 egységgel a plafontól (15.0 - 1.5)
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);  // Fordítsuk meg Z tengely mentén
    glBindTexture(GL_TEXTURE_2D, scene->csillar_texture);
    draw_model(&scene->csillar);
    glPopMatrix();

    
}

 void toggle_ajto() {
     if (!ajto_nyitva) {
         ajto_angle = 90.0f;        // Ajtó nyitása 90 fokra
         ajto_nyitva = true;
     } else {
         ajto_angle = 0.0f;          // Ajtó bezárása
         ajto_nyitva = false;
     }
 }
     