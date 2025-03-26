#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "assets/models/cube.obj");
    scene->texture_cube = load_texture("assets/textures/cube.png");
    
    load_model(&(scene->house), "assets/models/house.obj");
    scene->texture_house = load_texture("assets/textures/house.png");
    
    scene->rotation_angle = 0.0f;
    


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
}

void set_lighting()
{
    void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };  // Kikapcsolva
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Bekapcsolva
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Kikapcsolva
    float position[] = { 0.0f, 0.0f, 5.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Fényes csillogás
    float diffuse_light[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Kikapcsolva

    float ambient_light[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // Környezeti fény
    float diffuse_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };  // Kikapcsolva
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Kikapcsolva

//pl:
float ambient_light[] = { 0.2f, 0.2f, 0.2f, 1.0f };
float diffuse_light[] = { 0.8f, 0.8f, 0.8f, 1.0f };
float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };


}

}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
       
        scene->material.ambient = (Color){ 0.3f, 0.3f, 0.3f };
        scene->material.diffuse = (Color){ 0.2f, 0.2f, 0.2f };
        scene->material.specular = (Color){ 1.0f, 1.0f, 1.0f };
        scene->material.shininess = 100.0f;

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
        scene->rotation_angle += 1.0f;
        if (scene->rotation_angle > 360.0f) {
            scene->rotation_angle -= 360.0f;
        }
{
        static float rotation = 0.0;
        rotation += 45.0 * time;  // 45 fok másodpercenként

        glPushMatrix();
        glRotatef(rotation, 0, 1, 0);
        draw_model(&(scene->cube));
        glPopMatrix();
}
update_light_position(SDL_GetTicks() / 1000.0);
float intensity = (sin(SDL_GetTicks() / 1000.0) + 1) / 2; // 0 és 1 között oszcillál
float diffuse_light[] = { intensity, 0.5f * intensity, 1.0f - intensity, 1.0f };
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);

    }   

void render_scene(const Scene* scene)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            glPushMatrix();
            glTranslatef(i * 2.0, j * 2.0, 0);
            draw_model(&(scene->cube));
            glPopMatrix();
            glPushMatrix();
        }
    }
            set_material(&(scene->material));
            glBindTexture(GL_TEXTURE_2D, scene->texture_cube);
            draw_model(&(scene->cube));
            glPopMatrix();

            glPushMatrix();
            glTranslatef(3.0, 0.0, 0.0);
            glRotatef(scene->rotation_angle, 0, 1, 0);
            glBindTexture(GL_TEXTURE_2D, scene->texture_house);
            draw_model(&(scene->house));
            glPopMatrix();

            glPushMatrix();
            glTranslatef(house_position_x, 0.0, 0.0);
            glBindTexture(GL_TEXTURE_2D, scene->texture_house);
            draw_model(&(scene->house));
            glPopMatrix();
 
            glPushMatrix();
            glTranslatef(2.0, 2.0, 0.0);
            set_material(&(scene->material));
            draw_model(&(scene->cube));
            glPopMatrix();


            void render_scene2(const Scene* scene)
            {
                set_material(&(scene->material));
                set_lighting();
                
                // Kocka megjelenítése
                glPushMatrix();
                glTranslatef(-2.0, 0.0, 0.0);
                draw_model(&(scene->cube));
                glPopMatrix();

                // Ház megjelenítése
                glPushMatrix();
                glTranslatef(2.0, 0.0, 0.0);
                draw_model(&(scene->house));
                glPopMatrix();
            }

}

void draw_origin()
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
}

void set_colors()
{
    scene->material.diffuse.red = 0.0;
    scene->material.diffuse.green = 0.0;
    scene->material.diffuse.blue = 1.0;  // Kék színű lesz
}

void update_light_position(double time)
{
    float position[] = { 5.0f * cos(time), 2.0f, 5.0f * sin(time), 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

static float light_intensity = 1.0f;

void handle_app_events(){
case SDL_SCANCODE_UP:
    light_intensity = fmin(1.0f, light_intensity + 0.1f);
    break;
case SDL_SCANCODE_DOWN:
    light_intensity = fmax(0.0f, light_intensity - 0.1f);
    break;

    float diffuse_light[] = { light_intensity, light_intensity, light_intensity, 1.0f };
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);

}
