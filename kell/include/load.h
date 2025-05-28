#ifndef OBJ_LOAD_H
#define OBJ_LOAD_H

#include "model.h"

#include <stdio.h>

int load_model(Model* model, const char* filename);
void count_elements(Model* model, FILE* file);
int read_elements(Model* model, FILE* file);
ElementType calc_element_type(const char* text);
int read_vertex(Vertex* vertex, const char* text);
int read_texture_vertex(TextureVertex* texture_vertex, const char* text);
int read_normal(Vertex* normal, const char* text);
int read_triangle(Triangle* triangle, const char* text);
int is_numeric(char c);

#endif 
