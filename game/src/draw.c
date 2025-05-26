#include "draw.h"

#include <GL/gl.h>
#include <stdio.h>

void draw_model(const Model* model){
    printf("Rajzolas indult.\n");
    
    GLuint tex_id = 0;

    if (model->material.fa1_texture) tex_id = model->material.fa1_texture;
    else if (model->material.fa2_texture) tex_id = model->material.fa2_texture;
    else if (model->material.fa3_texture) tex_id = model->material.fa3_texture;
    else if (model->material.fa4_texture) tex_id = model->material.fa4_texture;
    else if (model->material.szek_texture) tex_id = model->material.szek_texture;
    else if (model->material.ajto_texture) tex_id = model->material.ajto_texture;
    else if (model->material.ajtob_texture) tex_id = model->material.ajtob_texture;
    else if (model->material.barna_texture) tex_id = model->material.barna_texture;
    else if (model->material.szonyeg_texture) tex_id = model->material.szonyeg_texture;
    else if (model->material.kek_texture) tex_id = model->material.kek_texture;
    else if (model->material.fal_texture) tex_id = model->material.fal_texture;
    else if (model->material.cserep_texture) tex_id = model->material.cserep_texture;
    else if (model->material.book_texture) tex_id = model->material.book_texture;
    else if (model->material.csillar_texture) tex_id = model->material.csillar_texture;

    if (tex_id != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_id);
    } else {
        glDisable(GL_TEXTURE_2D); // ha nincs textúra
    }

    draw_triangles(model);

    glDisable(GL_TEXTURE_2D);
}

void draw_triangles(const Model* model) {
    int i, k;
    int vertex_index, texture_index, normal_index;
    float x, y, z, u, v;

    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i) {
        for (k = 0; k < 3; ++k) {
            vertex_index = model->triangles[i].points[k].vertex_index;
            texture_index = model->triangles[i].points[k].texture_index;
            normal_index = model->triangles[i].points[k].normal_index;

            if (normal_index >= 0 && normal_index < model->n_normals) {
                x = model->normals[normal_index].x;
                y = model->normals[normal_index].y;
                z = model->normals[normal_index].z;
                glNormal3f(x, y, z);
            }

            if (texture_index >= 0 && texture_index < model->n_texture_vertices) {
                u = model->texture_vertices[texture_index].u;
                v = model->texture_vertices[texture_index].v;
                glTexCoord2f(u, 1.0f - v);
            }

            if (vertex_index >= 0 && vertex_index < model->n_vertices) {
                x = model->vertices[vertex_index].x;
                y = model->vertices[vertex_index].y;
                z = model->vertices[vertex_index].z;
                glVertex3f(x, y, z);
            }
        }
    }

    glEnd();
}
