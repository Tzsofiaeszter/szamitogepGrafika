#ifndef MODEL_H
#define MODEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

typedef struct Model {
    GLuint vao;        // tárolja az OpenGL objektumok pozicióját, színét, textúrák koordinátáit
    GLuint vbo;        // olyan OpenGL objektum, amely a csúcspontok adatait tárolja a grafikus kártya memóriájában, ezzel lehetővé teszi a gyorsabb adatátvitelt és rajzolást
    int vertexCount;   // Ez a változó tárolja a modell csúcspontjainak számát. Erre az információra van szükség az OpenGL rajzolási függvényeinek meghívásakor, hogy tudja, hány csúcspontot kell feldolgoznia
} Model;

Model loadModel(const char *filename);
void drawModel(const Model *model);

#endif