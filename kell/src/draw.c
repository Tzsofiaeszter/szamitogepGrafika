#include "draw.h"

#include <GL/gl.h>

void draw_model(const Model* model)
{
    draw_triangles(model);
}

void draw_triangles(const Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    float x, y, z, u, v;

   // Hat különböző szín (ismétlődnek 6 után)
    float colors[3][3] = {
        {1.0f, 0.0f, 0.0f},  // piros
        {0.0f, 1.0f, 0.0f},  // zöld
        {0.0f, 0.0f, 1.0f},  // kék
        //{1.0f, 1.0f, 0.0f},  // sárga
        //{1.0f, 0.0f, 1.0f},  // lila
        //{0.0f, 1.0f, 1.0f}   // cián
    };

    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i) {
        // Ismétlődő színek: 0–5 között
        int color_index = i % 3;
        glColor3f(
            colors[color_index][0],
            colors[color_index][1],
            colors[color_index][2]
        );

        for (k = 0; k < 3; ++k) {
            normal_index = model->triangles[i].points[k].normal_index;
            x = model->normals[normal_index].x;
            y = model->normals[normal_index].y;
            z = model->normals[normal_index].z;
            glNormal3f(x, y, z);

            texture_index = model->triangles[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            glTexCoord2f(u, 1.0 - v);

            vertex_index = model->triangles[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3f(x, y, z);
        }
    }

    glEnd();
}
