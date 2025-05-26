#include "render.h"

#include "app.h"
#include "camera.h" // Szükséges a kamera rotációjának eléréséhez
#include "scene.h"  // Szükséges a scene.segedkepernyo_texture és scene.eg_background_texture eléréséhez

#include <SDL2/SDL.h>
#include <GL/gl.h>          // OpenGL rendereléshez

void render_help_screen(const App* app)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, app->window_width, app->window_height, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, app->scene.segedkepernyo_texture);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(app->window_width, 0.0f);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f(app->window_width, app->window_height);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f(0.0f, app->window_height);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void render_skybox(const App* app)
{
    // 1. Ortho nézetre váltunk a képernyő méretéhez
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, app->window_width, app->window_height, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 2. Háttér: világítás, mélységi teszt kikapcsolása
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    // 3. Textúra bekapcsolás
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, app->scene.eg_background_texture);
    glColor3f(1, 1, 1);

    // 4. Teljes képernyőre kirajzolás
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(app->window_width, 0.0f);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f(app->window_width, app->window_height);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f(0.0f, app->window_height);
    glEnd();

    // 5. Állapot visszaállítása
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

