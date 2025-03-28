#include "matrix.h"
#include <stdio.h>
#include <math.h>

// Transzformációs mátrix verem inicializálása
void init_matrix_stack(MatrixStack* stack) {
    stack->top = -1; // A verem üres, nincs rajta elem
}

// Egységmátrix inicializálása
void init_identity_matrix(float matrix[3][3]) {
    init_zero_matrix(matrix);
    matrix[0][0] = 1.0f;
    matrix[1][1] = 1.0f;
    matrix[2][2] = 1.0f;
}

// Néhány alapvető művelet
void init_zero_matrix(float matrix[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Mátrix hozzáadása a veremhez
int push_matrix(MatrixStack* stack, const float matrix[3][3]) {
    if (stack->top < MAX_STACK_SIZE - 1) {
        stack->top++;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                stack->stack[stack->top][i][j] = matrix[i][j];
            }
        }
        return 1; // Sikeres push
    }
    return 0; // Verem tele
}

// Mátrix eltávolítása a verem tetejéről
int pop_matrix(MatrixStack* stack, float matrix[3][3]) {
    if (stack->top >= 0) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                matrix[i][j] = stack->stack[stack->top][i][j];
            }
        }
        stack->top--; // Csökkentjük a verem tetejét
        return 1; // Sikeres pop
    }
    return 0; // Verem üres
}

// Mátrix szorzás egy skalárral
void scalar_multiply_matrix(float matrix[3][3], float scalar) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] *= scalar;
        }
    }
}

// Mátrixok szorzása
void multiply_matrices(const float a[3][3], const float b[3][3], float c[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            c[i][j] = 0.0f;
            for (int k = 0; k < 3; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// Pont transzformálása
void transform_point(const float matrix[3][3], float point[3]) {
    float x = point[0];
    float y = point[1];
    point[0] = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2];
    point[1] = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2];
    point[2] = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2];
}

// Transzformációk

void scale(float matrix[3][3], float sx, float sy) {
    float scale_matrix[3][3];
    init_identity_matrix(scale_matrix);
    scale_matrix[0][0] = sx;
    scale_matrix[1][1] = sy;
    multiply_matrices(matrix, scale_matrix, matrix);
}

void shift(float matrix[3][3], float tx, float ty) {
    float shift_matrix[3][3];
    init_identity_matrix(shift_matrix);
    shift_matrix[0][2] = tx;
    shift_matrix[1][2] = ty;
    multiply_matrices(matrix, shift_matrix, matrix);
}

void rotate(float matrix[3][3], float angle) {
    float rotate_matrix[3][3];
    init_identity_matrix(rotate_matrix);
    float radians = angle * (M_PI / 180.0f); // Convert to radians
    rotate_matrix[0][0] = cos(radians);
    rotate_matrix[0][1] = -sin(radians);
    rotate_matrix[1][0] = sin(radians);
    rotate_matrix[1][1] = cos(radians);
    multiply_matrices(matrix, rotate_matrix, matrix);
}
