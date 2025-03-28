#ifndef MATRIX_H
#define MATRIX_H

#define MAX_STACK_SIZE 10

typedef struct {
    float stack[MAX_STACK_SIZE][3][3]; 
} MatrixStack;


void init_zero_matrix(float matrix[3][3]);

void init_identity_matrix(float matrix[3][3]);

int push_matrix(MatrixStack* stack, const float matrix[3][3]);

int pop_matrix(MatrixStack* stack, float matrix[3][3]);

void print_matrix(const float matrix[3][3]);

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

void scalar_multiply_matrix(float matrix[3][3], float scalar);

void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

void transform_point(const float matrix[3][3], float point[3]);

void scale(float matrix[3][3], float sx, float sy);

void shift(float matrix[3][3], float tx, float ty);

void rotate(float matrix[3][3], float angle);

#endif 
