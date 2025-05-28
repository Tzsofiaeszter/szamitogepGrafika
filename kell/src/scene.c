#include "scene.h"

#include <load.h>
#include <draw.h>


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

    //load_model(&(scene->pufika), "assets/models/pufika.obj");
    //scene->kek_texture_id = load_texture("assets/textures/kek.png");

    //load_model(&(scene->ora), "assets/models/ora.obj");
    //scene->fa3_texture_id = load_texture("assets/textures/fa3.png");


    scene->help_texture_id = load_texture("assets/textures/help.png");


    //glBindTexture(GL_TEXTURE_2D,scene->kek_texture_id);

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

// mozgatható székek pozíciója
    scene->szek1_position[0] = -1.0f;
    scene->szek1_position[1] = -1.0f;
    scene->szek1_position[2] = -1.95f;

    scene->szek2_position[0] = -1.0f;
    scene->szek2_position[1] = 0.5f;
    scene->szek2_position[2] = -1.95f;



}

//void set_lighting()
void set_lighting(const Scene* scene){
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    //float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };

    float diffuse_light[] = {
    scene->light_intensity,
    scene->light_intensity,
    scene->light_intensity,
    1.0f
};
    
float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
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
}

void render_scene(const Scene* scene){

    set_material(&(scene->material));
    //set_lighting();
    //draw_origin();

    

if (scene->lighting_enabled) {
    glEnable(GL_LIGHTING);
} else {
    glDisable(GL_LIGHTING);
}

set_lighting(scene);


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
    glTranslatef(scene->szek1_position[0], scene->szek1_position[1], scene->szek1_position[2]);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->szek));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->szek_texture_id); 
    glTranslatef(scene->szek2_position[0], scene->szek2_position[1], scene->szek2_position[2]);
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
        glTexCoord2f(1.0, 1.0); glVertex2f(-1.0, -1.0);  // bal alsó
        glTexCoord2f(0.0, 1.0); glVertex2f( 1.0, -1.0);  // jobb alsó
        glTexCoord2f(0.0, 0.0); glVertex2f( 1.0,  1.0);  // jobb felső
        glTexCoord2f(1.0, 0.0); glVertex2f(-1.0,  1.0);  // bal felső
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


void move_szek1(Scene* scene, float dx, float dy, float dz) {
    scene->szek1_position[0] += dx;
    scene->szek1_position[1] += dy;
    scene->szek1_position[2] += dz;
}


void move_szek2(Scene* scene, float dx, float dy, float dz) {
    scene->szek2_position[0] += dx;
    scene->szek2_position[1] += dy;
    scene->szek2_position[2] += dz;
}
