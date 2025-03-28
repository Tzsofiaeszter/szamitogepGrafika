#include "matrix.h"
#include <stdio.h>

int main() {
    // Verem inicializálása
    MatrixStack stack;
    init_matrix_stack(&stack);

    // Mátrixok inicializálása
    float matrix[3][3];
    init_identity_matrix(matrix);
    print_matrix(matrix);
    
    // Transzformációk
    scale(matrix, 2.0f, 2.0f);
    push_matrix(&stack, matrix);
    printf("Scaled matrix:\n");
    print_matrix(matrix);
    
    // Eltolás
    shift(matrix, 3.0f, 4.0f);
    push_matrix(&stack, matrix);
    printf("Shifted matrix:\n");
    print_matrix(matrix);
    
    // Visszavonás (pop) - Előző állapotok visszaállítása
    pop_matrix(&stack, matrix);
    printf("After pop (Shifted back):\n");
    print_matrix(matrix);
    
    pop_matrix(&stack, matrix);
    printf("After pop (Scaled back):\n");
    print_matrix(matrix);

    return 0;
}
