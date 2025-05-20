#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H

#define TRUE 1
#define FALSE 0

#include <GL/gl.h>
#define INVALID_VERTEX_INDEX 0

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

typedef struct {
    float red;
    float green;
    float blue;
} Color;

typedef struct {
    Color ambient;
    Color diffuse;
    Color specular;
    float shininess;
    GLuint texture_id;
} Material;

typedef struct {
    Vec3 pozicio;
    Vec3 forgatas;
    Vec3 skalazas;
} Transform;

typedef struct {
    double x;
    double y;
    double z;
} Vertex;

typedef struct {
    double u;
    double v;
} TextureVertex;

typedef struct {
    int vertex_index;
    int texture_index;
    int normal_index;
} FacePoint;

typedef struct {
    FacePoint points[3];
} Triangle;

typedef struct {
    float* vertices;
    float* texcoords;
    float* normals;
    unsigned int* indices;
    int vertex_count;
    int index_count;
} Mesh;                  // 3szögek miatt             

typedef struct {
    int n_vertices;
    int n_texture_vertices;
    int n_normals;
    int n_triangles;
    
    Vertex* vertices;
    TextureVertex* texture_vertices;
    Vertex* normals;
    Triangle* triangles;   // ez a 3szögek "nyers" formája
    Mesh mesh;             // ez pedig amit ki tud olvasni
    
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

double degree_to_radian(double degree);

#endif  
