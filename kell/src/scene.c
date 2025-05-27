#include "scene.h"

#include <load.h>
#include <draw.h>


void init_scene(Scene* scene)
{
    load_model(&(scene->szoba), "assets/models/szoba.obj");
    load_model(&(scene->asztalka), "assets/models/asztalka.obj");
    load_model(&(scene->szonyegke), "assets/models/szonyegke.obj");
    load_model(&(scene->csillarka), "assets/models/csillarka.obj");
    load_model(&(scene->szek), "assets/models/szek.obj");
    load_model(&(scene->konyvespolc), "assets/models/konyvespolc.obj");


    
    //scene->texture_id = load_texture("assets/textures/fal.png");
    //scene->texture_id = load_texture("assets/textures/csillar.png");


    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

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

    scene->lighting_enabled = true;

}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
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

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene){

    set_material(&(scene->material));
    set_lighting();
    //draw_origin();

    glPushMatrix();
    draw_model(&(scene->szoba));
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5f, 0.25f, 0.1f);
    glTranslatef(0.0f, 0.0f, -1.8f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->asztalka));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.98f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->szonyegke));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.8f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->csillarka));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, -1.0f, -1.95f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->szek));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, 0.5f, -1.95f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    draw_model(&(scene->szek));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5f, 1.0f, -1.95f);  
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    draw_model(&(scene->konyvespolc));
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