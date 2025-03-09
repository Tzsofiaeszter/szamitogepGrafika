#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MATRIX_SIZE 4

typedef struct {
    float matrices[MAX_STACK_SIZE][MATRIX_SIZE][MATRIX_SIZE];
    int top;
} MatrixStack;

void init_stack(MatrixStack *stack) {
    stack->top = -1;
}

int push_matrix(MatrixStack *stack, float matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    if (stack->top >= MAX_STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        return 0;
    }
    stack->top++;
    memcpy(stack->matrices[stack->top], matrix, sizeof(float) * MATRIX_SIZE * MATRIX_SIZE);
    return 1;
}

int pop_matrix(MatrixStack *stack, float matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    if (stack->top < 0) {
        printf("Stack underflow!\n");
        return 0;
    }
    memcpy(matrix, stack->matrices[stack->top], sizeof(float) * MATRIX_SIZE * MATRIX_SIZE);
    stack->top--;
    return 1;
}

void print_matrix(float matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    MatrixStack stack;
    init_stack(&stack);

    float identity[MATRIX_SIZE][MATRIX_SIZE] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    float transform[MATRIX_SIZE][MATRIX_SIZE] = {
        {1, 0, 0, 2},
        {0, 1, 0, 3},
        {0, 0, 1, 4},
        {0, 0, 0, 1}
    };

    printf("Pushing identity matrix:\n");
    push_matrix(&stack, identity);
    print_matrix(identity);

    printf("Pushing transformation matrix:\n");
    push_matrix(&stack, transform);
    print_matrix(transform);

    printf("Popping last matrix:\n");
    float popped[MATRIX_SIZE][MATRIX_SIZE];
    pop_matrix(&stack, popped);
    print_matrix(popped);

    printf("Popping again to get back to identity matrix:\n");
    pop_matrix(&stack, popped);
    print_matrix(popped);

    return 0;
}
