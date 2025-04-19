#include "camera.h"
#include <GL/gl.h>
#include <math.h>


void initCamera(Camera *camera) {    // kamera kezdeti inicializálása
   //pozíció
    camera->position.x = 0.0f;
    camera->position.y = 0.0f;
    camera->position.z = 5.0f;

    //forgás
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;

    //sebesség
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    
    camera->is_preview_visible = false;
}

void updateCamera(Camera *camera, const SDL_Event *event) {
    float cameraSpeed = 0.1f;             // 0.1 egységet mozdul minden billenytűzet leütésekor (lassabb mozgást tesz lehtővé)
    float mouseSensitivity = 0.1f;        // 0.1-szeresen a kamera forgatását befolyásolja az egér használatával (egérrel forog körbe a térben)

    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    if (event->type == SDL_KEYDOWN) {    // leellenőrzi , hogy volt-e billentyű lenyomás ha igen , akkor az aálábbiakat futtatja le
        switch (event->key.keysym.sym) { //event->key.keysym.sym azt jelenti, hogy megnézzük, melyik billentyűt nyomták le awsd billenytűk beállítása
            case SDLK_w: //előre                // SDLK jelentése hogy akkor fut le mikor leütjük a megfelelő bilentyűt
                camera->position.x += cameraSpeed * cos(angle) * camera->speed.y * time;
                camera->position.z += cameraSpeed * sin(angle) * camera->speed.y * time;
                break;
            case SDLK_s: //hátra
                camera->position.x -= cameraSpeed * cos(angle) * camera->speed.y  * time;
                camera->position.z -= cameraSpeed * sin(angle) * camera->speed.y  * time;
                break;
            case SDLK_a:  //balra                //cos() radiánban várja a szöget és a megfelelő értékre konvertálja
                camera->position.x += cameraSpeed * cos(side_angle) * camera->speed.x * time;
                camera->position.z += cameraSpeed * sin(side_angle) * camera->speed.x * time;
                break;
            case SDLK_d://jobbra
                camera->position.x -= cameraSpeed * cos(side_angle) * camera->speed.x * time;
                camera->position.z -= cameraSpeed * sin(side_angle) * camera->speed.x * time;
                break;
            default:
                break;
        }
    } else if (event->type == SDL_MOUSEMOTION) {    // Van-e egérmozgatás, ha igen az alábbiak futnak le
        camera->rotation.z += event->motion.xrel * mouseSensitivity;  // A kamera Z tengely körüli forgatása (vízszintes irány)
        camera->rotation.y -= event->motion.yrel * mouseSensitivity;  // A kamera Y tengely körüli forgatása (függőleges irány)
    
        // Túlzott dőlés megakadályozása
        if (camera->rotation.y > 89.0f)    // Ha a dőlésszög nagyobb, mint 89 fok, akkor 89-re állítjuk
            camera->rotation.y = 89.0f;
        if (camera->rotation.y < -89.0f)   // Ha a dőlésszög kisebb, mint -89 fok, akkor -89-re állítjuk
            camera->rotation.y = -89.0f;
    }
    
}

// kamera OpenGL beállításának megfelelően: pozíció és irány
void set_view(const Camera *camera) {           
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0f, 0.0f, 0.0f); // dőlés              // Ez a sor elforgatja a teljes 3D-s világot a kamera "dőlés" (pitch) szöge alapján; glRotatef() egy OpenGL függvény, ami elforgatja a 3D-s teret; -camera->pitch azt jelenti, hogy a forgatás a kamera dőlésének ellentétes irányába történik; 1.0f, 0.0f, 0.0f azt jelenti, hogy az x tengely körül forgatunk
    glRotatef(-(camera->rotation.z - 90), 0.0f, 1.0f, 0.0f); // irány              // uez; csak itt a forgatás irányában és az y tengely mentén
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z); // elmozdítás      // glTranslatef() egy OpenGL függvény, ami eltolja a 3D-s teret, az ellentétes irányba!!!
}

// beállítja az OpenGL vetítési mátrixot, ami meghatározza, hogyan jelenjen meg a 3D-s világ
void setProjection(const Camera *camera, int width, int height) {
    glMatrixMode(GL_PROJECTION);   // a sor azt mondja az OpenGL-nek, hogy a következő mátrixműveletek a vetítési mátrixot érintik
    glLoadIdentity();              // alaphelyzetbe állítja a vetítési mátrixot

    gluPerspective(camera->latoszog, (float)width / (float)height, 0.1f, 100.0f); // perspektivikus vetítés: látószög; képernyő arány; legközelebbi és legtávolabbi látható pontok
    glMatrixMode(GL_MODELVIEW);    // a sor azt mondja az OpenGL-nek, hogy a következő mátrixműveletek a modellnézeti mátrixot érintik
}


void rotate_camera(Camera* camera, double horizontal, double vertical){
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

// Sebesség beállítása
void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

// Oldalirányú sebesség beállítása
void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);           // Ne legyen világítás, csak a textúrát lássuk
    glDisable(GL_DEPTH_TEST);         // Ne számoljon mélységet – mindig jelenjen meg elöl
    glEnable(GL_COLOR_MATERIAL);      // Anyagszín engedélyezése 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                 // Alapnézet – nem veszi figyelembe a kamerát

    /*glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);*/
}
