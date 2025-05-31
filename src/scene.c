#include "scene.h"

#include <load.h>
#include <draw.h>
#include <stdlib.h>


void init_scene(Scene* scene){

    scene->lighting_enabled = true;
    scene->show_help_visible = false;
    scene->light_intensity = 1.0f;


    load_model(&(scene->szoba), "assets/models/szoba.obj");
    scene->fal_texture_id = load_texture("assets/textures/fal.png");
    
    load_model(&(scene->asztalka), "assets/models/asztalka.obj");
    scene->fa2_texture_id = load_texture("assets/textures/fa2.png");

    load_model(&(scene->szonyegke), "assets/models/szonyegke.obj");
    scene->kek_texture_id = load_texture("assets/textures/kek.png");

    load_model(&(scene->csillarka), "assets/models/csillarka.obj");
    scene->csillar_texture_id = load_texture("assets/textures/csillar.png");

    load_model(&(scene->szek), "assets/models/szek.obj");
    scene->szek_texture_id = load_texture("assets/textures/szek.png");

    load_model(&(scene->konyvespolc), "assets/models/konyvespolc.obj");
    scene->fa0_texture_id = load_texture("assets/textures/fa0.png");

    load_model(&(scene->book1), "assets/models/book1.obj");
    scene->book1_texture_id = load_texture("assets/textures/book1.png");

    load_model(&(scene->book2), "assets/models/book2.obj");
    scene->book2_texture_id = load_texture("assets/textures/book2.png");

    load_model(&(scene->gyep), "assets/models/gyep.obj");
    scene->gyep_texture_id = load_texture("assets/textures/gyep.png");

    load_model(&(scene->fa1), "assets/models/fa1.obj");
    scene->facska1_texture_id = load_texture("assets/textures/facska1.png");
   

    //load_model(&(scene->pufika), "assets/models/pufika.obj");
    //scene->kek_texture_id = load_texture("assets/textures/kek.png");

    //load_model(&(scene->ora), "assets/models/ora.obj");
    //scene->fa3_texture_id = load_texture("assets/textures/fa3.png");


    scene->help_texture_id = load_texture("assets/textures/help.png");

    //scene->sky_top_texture_id = load_texture("assets/textures/eg.png");
    scene->sky_side_texture_id = load_texture("assets/textures/eg_oldalt.png");

    //glBindTexture(GL_TEXTURE_2D,scene->kek_texture_id);

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 0.2;
    scene->material.diffuse.green = 0.2;
    scene->material.diffuse.blue = 0.2;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 20.0;

// mozgatható székek pozíciója
    scene->szek1_position.x = -1.0f;
    scene->szek1_position.y = -1.0f;
    scene->szek1_position.z = -1.95f;

    scene->szek2_position.x = -1.0f;
    scene->szek2_position.y = 0.5f;
    scene->szek2_position.z = -1.95f;
    
    
    
    scene->rain_enabled = true;

    for (int i = 0; i < MAX_RAINDROPS; i++) {        // 20*20-as négyzeten esik az eső
        scene->raindrops[i].position.x = ((float)rand() / RAND_MAX) * 30.0f - 5.0f;  //Ez a sor egy olyan x koordinátát állít be az i-edik esőcsepp pozíciójához, ami véletlenszerűen van elosztva -5 és +25 között.
        scene->raindrops[i].position.y = ((float)rand() / RAND_MAX) * 30.0f - 5.0f;
        scene->raindrops[i].position.z = ((float)rand() / RAND_MAX) * 5.0f + 5.0f; 
        scene->raindrops[i].speed = 0.01f + ((float)rand() / RAND_MAX) * 0.02f;
    }

    scene->lightning_active = false;
    scene->lightning_intensity = 0.0f;
    scene->lightning_timer = 0;
    scene->lightning_cooldown = rand() % 100 + 200;  

}

//void set_lighting()
void set_lighting(const Scene* scene) {
    float base_intensity = scene->light_intensity;

    // Villámlás fény, maximum 1.0-ig
    float lightning_intensity = scene->lightning_intensity;
    float final_intensity = base_intensity + lightning_intensity;
    if (final_intensity > 1.5f) final_intensity = 1.5f;

    float ambient_ratio = 0.2f;
    float diffuse_ratio = 0.6f;
    float specular_ratio = 0.4f;

    float ambient_light[] = {
        ambient_ratio * final_intensity,
        ambient_ratio * final_intensity,
        ambient_ratio * final_intensity,
        1.0f
    };

    float diffuse_light[] = {
        diffuse_ratio * final_intensity,
        diffuse_ratio * final_intensity,
        diffuse_ratio * final_intensity,
        1.0f
    };

    float specular_light[] = {
        specular_ratio * final_intensity,
        specular_ratio * final_intensity,
        specular_ratio * final_intensity,
        1.0f
    };

    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}


void increase_light(Scene* scene) {
    scene->light_intensity += 0.1f;
    if (scene->light_intensity > 1.0f) {
        scene->light_intensity = 1.0f;
    }
}

void decrease_light(Scene* scene) {
    scene->light_intensity -= 0.1f;
    if (scene->light_intensity < 0.0f) {
        scene->light_intensity = 0.0f;
    }
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

void update_scene(Scene* scene) {
// ESŐ
    if (scene->rain_enabled) {
        for (int i = 0; i < MAX_RAINDROPS; ++i) {
            scene->raindrops[i].position.z -= scene->raindrops[i].speed;
           if (scene->raindrops[i].position.z < -2.0f) {
                scene->raindrops[i].position.z = 10.0f;
                scene->raindrops[i].position.x = ((float)rand() / RAND_MAX) * 20.0f - 5.0f; // esőcseppeket állítja be hgy ne ugyanoda essenek egy 20-as tartományban 5 eltolással jelenjenek meg
                scene->raindrops[i].position.y = ((float)rand() / RAND_MAX) * 20.0f - 5.0f;
            }
        }
    }
// VILLÁMLÁS
    if (scene->lightning_active) {
    scene->lightning_timer--;
    float progress = (float)scene->lightning_timer / 20.0f; // hosszabb idő, 20 frame
    if (progress > 0.5f) {
        scene->lightning_intensity = 1.5f * (1.0f - progress);  // intenzitás 1.5x
    } else {
        scene->lightning_intensity = 1.5f * progress;
    }
    if (scene->lightning_timer <= 0) {
        scene->lightning_active = false;
        scene->lightning_intensity = 0.0f;
        scene->lightning_cooldown = rand() % 150 + 100;  // rövidebb várakozás a következő villámlásig
        printf("Lightning ended, cooldown set to %d\n", scene->lightning_cooldown);
    }
} else {
    scene->lightning_cooldown--;
    if (scene->lightning_cooldown <= 0) {
        scene->lightning_active = true;
        scene->lightning_timer = 20;  // hosszabb villanás
        printf("Lightning started\n");
    }
}


}


void render_scene(const Scene* scene){

    set_material(&(scene->material));

    if (scene->lighting_enabled) {
        glEnable(GL_LIGHTING);
    } else {
        glDisable(GL_LIGHTING);
    }

    set_lighting(scene);

    glPushMatrix();
    draw_skybox(scene, 50.0f); 
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->fal_texture_id); 
    draw_model(&(scene->szoba));
    glPopMatrix();

    glPushMatrix(); 
    glBindTexture(GL_TEXTURE_2D, scene->fa2_texture_id); 
    //glColor3f(0.5f, 0.25f, 0.1f);               // barna
    glTranslatef(0.0f, 0.0f, -1.8f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->asztalka));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->kek_texture_id); 
    glTranslatef(0.0f, 0.0f, -1.98f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->szonyegke));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->csillar_texture_id); 
    glTranslatef(0.0f, 0.0f, 1.8f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->csillarka));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->szek_texture_id); 
    glTranslatef(scene->szek1_position.x, scene->szek1_position.y, scene->szek1_position.z);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->szek));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->szek_texture_id); 
    glTranslatef(scene->szek2_position.x, scene->szek2_position.y, scene->szek2_position.z);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->szek));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->fa0_texture_id); 
    glTranslatef(-1.5f, 1.0f, -1.98f);  
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    draw_model(&(scene->konyvespolc));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->book1_texture_id); 
    glTranslatef(-1.0f, 1.5f, -1.0f);  
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    draw_model(&(scene->book1));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->book2_texture_id); 
    glTranslatef(-1.9f, 1.0f, -1.4f);  
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    draw_model(&(scene->book2));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->gyep_texture_id); 
    glTranslatef(0.0f, 0.0f, -2.3f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    draw_model(&(scene->gyep));
    glPopMatrix();

// KÜLTÉR    
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->facska1_texture_id); 
    glTranslatef(0.0f, 9.5f, -2.3f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    draw_model(&(scene->fa1));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->facska1_texture_id); 
    glTranslatef(5.5f, 9.5f, -2.3f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    draw_model(&(scene->fa1));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->facska1_texture_id); 
    glTranslatef(0.0f, -9.5f, -2.3f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    draw_model(&(scene->fa1));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->facska1_texture_id); 
    glTranslatef(-10.0f, -10.5f, -2.3f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    draw_model(&(scene->fa1));
    glPopMatrix();


    if (scene->rain_enabled) {
        glDisable(GL_LIGHTING);
        glColor3f(0.6f, 0.6f, 1.0f); // halványkék

       glBegin(GL_LINES);
   for (int i = 0; i < MAX_RAINDROPS; ++i) {
    vec3 p = scene->raindrops[i].position;

    glColor3f(0.5f, 0.5f, 1.0f);  // halványkék árnyalat, opcionális
    glVertex3f(p.x, p.y, p.z);         // felső pont
    glVertex3f(p.x, p.y, p.z - 0.2f);  // alsó pont (lefelé z-ben)
}
        glEnd();
        glEnable(GL_LIGHTING);
    }



}

/*void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}*/


void render_help_overlay(const Scene* scene) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);  // ortografikus vetítés 2D-hez

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->help_texture_id);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);    // a textúra bal felső sarka 
        glVertex2f(-1.0, -1.0);    // a képernyő bal alsó sarka
        glTexCoord2f(1.0, 1.0); 
        glVertex2f( 1.0, -1.0);
        glTexCoord2f(1.0, 0.0); 
        glVertex2f( 1.0,  1.0);
        glTexCoord2f(0.0, 0.0); 
        glVertex2f(-1.0,  1.0);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


void move_szek1(Scene* scene, float dx, float dy, float dz) {
    scene->szek1_position.x += dx;
    scene->szek1_position.y += dy;
    scene->szek1_position.z += dz;
}

void move_szek2(Scene* scene, float dx, float dy, float dz) {
    scene->szek2_position.x += dx;
    scene->szek2_position.y += dy;
    scene->szek2_position.z += dz;
}


void draw_skybox(const Scene* scene, float size) {
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);  // hogy ne zavarja a mélységi teszt a skyboxot

    float s = size / 2.0f;

    glBindTexture(GL_TEXTURE_2D, scene->sky_side_texture_id);

    // Tető
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);      // Textúra koordináta: (0, 0) → textúra bal alsó sarka
        glVertex3f(-s, s, -s);  // Csúcspont (vertex): (-s, s, -s) → térbeli pozíció: bal-hátul-fent
        glTexCoord2f(1,0); 
        glVertex3f(s, s, -s);
        glTexCoord2f(1,1); 
        glVertex3f(s, s, s);
        glTexCoord2f(0,1); 
        glVertex3f(-s, s, s);
    glEnd();

    // Elülső
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(-s, -s, s);
        glTexCoord2f(1,0); glVertex3f(s, -s, s);
        glTexCoord2f(1,1); glVertex3f(s, s, s);
        glTexCoord2f(0,1); glVertex3f(-s, s, s);
    glEnd();

    // Hátsó
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(s, -s, -s);
        glTexCoord2f(1,0); glVertex3f(-s, -s, -s);
        glTexCoord2f(1,1); glVertex3f(-s, s, -s);
        glTexCoord2f(0,1); glVertex3f(s, s, -s);
    glEnd();

    // Bal oldal
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(-s, -s, -s);
        glTexCoord2f(1,0); glVertex3f(-s, -s, s);
        glTexCoord2f(1,1); glVertex3f(-s, s, s);
        glTexCoord2f(0,1); glVertex3f(-s, s, -s);
    glEnd();

    // Jobb oldal
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(s, -s, s);
        glTexCoord2f(1,0); glVertex3f(s, -s, -s);
        glTexCoord2f(1,1); glVertex3f(s, s, -s);
        glTexCoord2f(0,1); glVertex3f(s, s, s);
    glEnd();

    // Alja
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(-s, -s, -s);
        glTexCoord2f(1,0); glVertex3f(s, -s, -s);
        glTexCoord2f(1,1); glVertex3f(s, -s, s);
        glTexCoord2f(0,1); glVertex3f(-s, -s, s);
    glEnd();

    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
    //glDisable(GL_TEXTURE_2D);
}





