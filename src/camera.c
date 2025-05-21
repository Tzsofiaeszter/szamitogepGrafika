#include "camera.h"
#include"scene_manager.h"

#include <GL/gl.h>
#include <math.h>

// Segédfüggvény: fok értéket konvertál radiánba

    double degree_to_radian(double degree);

/*
Szög normalizálása 0–360 fok közé
 - Hasznos forgatásoknál, hogy ne lépjük túl az érvényes tartományt
*/
    static double normalize_angle(double angle) {
        while (angle < 0.0) angle += 360.0;
        while (angle >= 360.0) angle -= 360.0;
        return angle;
    }

/*
Kamera inicializálása alapértékekre
 - Pozíció, forgatás, sebesség nullázása
 - Előnézeti nézet kikapcsolása
*/
    void init_camera(Camera* camera){
        camera->position.x = 0.0;
        camera->position.y = 0.0;
        camera->position.z = 1.0;
        camera->rotation.x = 0.0;
        camera->rotation.y = 0.0;
        camera->rotation.z = 0.0;
        camera->speed.x = 0.0;
        camera->speed.y = 0.0;
        camera->speed.z = 0.0;

        camera->is_preview_visible = false;
    }

/*
Kamera pozíció frissítése az idő és sebesség alapján
 - Előre/hátra és oldalirányú mozgás számítása a forgatás szögével
*/
    void update_camera(Camera* camera, double time){
        double angle;
        double side_angle;

        angle = degree_to_radian(camera->rotation.z);
        side_angle = degree_to_radian(camera->rotation.z + 90.0);

        camera->position.x += cos(angle) * camera->speed.y * time;
        camera->position.y += sin(angle) * camera->speed.y * time;
        camera->position.x += cos(side_angle) * camera->speed.x * time;
        camera->position.y += sin(side_angle) * camera->speed.x * time;
    }

/*
Nézetmátrix beállítása a kamera pozíciója és forgatása alapján
 - OpenGL modell-nézet transzformáció beállítása
*/
    void set_view(const Camera* camera){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
        glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
        glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
    }

/*
Kamera forgatásának frissítése
 - A vízszintes (Z tengely) és függőleges (X tengely) szögek hozzáadása
 - Az értékek normalizálása 0–360 fokra
*/
    void rotate_camera(Camera* camera, double horizontal, double vertical) {
        camera->rotation.z = normalize_angle(camera->rotation.z + horizontal);
        camera->rotation.x = normalize_angle(camera->rotation.x + vertical);
    }

/*
Kamera előre/hátra sebességének beállítása
 - Y irányú mozgást szabályozza
*/
    void set_camera_speed(Camera* camera, double speed){
        camera->speed.y = speed;
    }

/*
Kamera oldalirányú sebességének beállítása
 - X irányú mozgást szabályozza
*/
    void set_camera_side_speed(Camera* camera, double speed){
        camera->speed.x = speed;
    }

/*
Textúra előnézet megjelenítése a képernyőn
 - Világítás és mélységi teszt kikapcsolása
 - Egyszerű 2D-s nézet létrehozása
 - Textúra kirajzolása egy négyzetre (quad)
 - Állapotok visszaállítása
*/
    void show_texture_preview(void) {
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -3.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -3.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -3.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -3.0f);
        glEnd();

        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
    }
