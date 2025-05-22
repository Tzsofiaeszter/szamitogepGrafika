#include "model.h"

#include <stdlib.h>
#include <math.h>

    #ifndef M_PI
    #define M_PI 3.14159265358979323846
    #endif

// Átalakítja a fokot radiánná 
    static double degree_to_radian(double degree){
        return degree * M_PI / 180.0;
    }

// Inicializálja a modell struktúrát, nullázza az összes adatot 
    void init_model(Model* model){
        if (model) {
            model->n_vertices = 0;
            model->n_texture_vertices = 0;
            model->n_normals = 0;
            model->n_triangles = 0;
            model->vertices = NULL;
            model->texture_vertices = NULL;
            model->normals = NULL;
            model->triangles = NULL;
    }
}

//Memóriát foglal a modell elemei számára, előre megadott elemszám alapján
    void allocate_model(Model* model){
        if (model) {
            model->vertices =
                (Vertex*)malloc((model->n_vertices + 1) * sizeof(Vertex));
            model->texture_vertices =
                (TextureVertex*)malloc((model->n_texture_vertices + 1) * sizeof(TextureVertex));
            model->normals =
                (Vertex*)malloc((model->n_normals + 1) * sizeof(Vertex));
            model->triangles =
            (Triangle*)malloc(model->n_triangles * sizeof(Triangle));
    }
    }

//Felszabadítja a modell által lefoglalt memóriát, és újrainicializálja az adatokat
    void free_model(Model* model){
        if (model) {
            if (model->vertices != NULL) {
                free(model->vertices);
                model->vertices = NULL;
            }
            if (model->texture_vertices != NULL) {
                free(model->texture_vertices);
                model->texture_vertices = NULL;
            }
            if (model->normals != NULL) {
                free(model->normals);
                model->normals = NULL;
            }
            if (model->triangles != NULL) {
                free(model->triangles);
                model->triangles = NULL;
            }
            init_model(model);
        }
    }