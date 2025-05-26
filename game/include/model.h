#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H

#include "utils.h"

#define TRUE 1
#define FALSE 0

#define INVALID_VERTEX_INDEX 0

typedef struct Vertex{
    double x;
    double y;
    double z;
} Vertex;

typedef struct TextureVertex{
    double u;
    double v;
} TextureVertex;

typedef struct FacePoint{
    int vertex_index;
    int texture_index;
    int normal_index;
} FacePoint;

typedef struct Triangle{
    struct FacePoint points[3];
} Triangle;

typedef struct Model{
    int n_vertices;
    int n_texture_vertices;
    int n_normals;
    int n_triangles;
    Vertex* vertices;
    TextureVertex* texture_vertices;
    Vertex* normals;
    Triangle* triangles;
    Material material;
} Model;

typedef enum {
    NONE,
    VERTEX,
    TEXTURE_VERTEX,
    NORMAL,
    FACE
} ElementType;

void init_model(Model* model);
void allocate_model(Model* model);
void free_model(Model* model);

#endif
