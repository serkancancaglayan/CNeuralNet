#include "Matrix.h"

Matrix *create_matrix(int rows, int cols){
    Matrix *new_matrix = (Matrix *) malloc(sizeof(Matrix));
    new_matrix->data = (float *) malloc(sizeof(float) * rows * cols);
    if(new_matrix == NULL){
        printf("Memory Allocation Error !");
        exit(EXIT_FAILURE);
    }
    new_matrix->rows = rows;
    new_matrix->cols = cols;
    return new_matrix;
}

int linear_index(int x, int y, int cols){
    return x * cols + y;
}

void fill_matrix_const(Matrix *matrix, double n){
    if(matrix == NULL){
        printf("Null pointer!");
        exit(EXIT_FAILURE);
    }
    if (matrix->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    int m_size = matrix->rows * matrix->cols;
    for(int i = 0; i < m_size; i++){
        matrix->data[i] = n;
    }
}
double rand_double(double min, double max){
    double range = max - min;
    double scaled = (double)rand() / RAND_MAX;
    return min + scaled * range;
}

void fill_matrix_rand(Matrix *matrix, double min, double max){
    if(matrix == NULL){
        printf("Null pointer!");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    if (matrix->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    int m_size = matrix->rows * matrix->cols;
    for(int i = 0; i < m_size; i++){
        matrix->data[i] = rand_double(min, max);
    }
}

Matrix *transpose(Matrix* matrix){
    if(matrix == NULL){
        printf("Null pointer!");
        exit(EXIT_FAILURE);
    }
    if (matrix->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    Matrix *n_matrix = create_matrix(matrix->cols, matrix->rows);
    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            n_matrix->data[linear_index(j, i, n_matrix->cols)] = matrix->data[linear_index(i, j, matrix->cols)];
        }
    }
    return n_matrix;
}

void display_matrix(Matrix *matrix){
    if(matrix == NULL){
        printf("Null pointer!");
        exit(EXIT_FAILURE);
    }
    if (matrix->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    printf("\n");
    printf("Matrix  dimensions are (%d, %d)\n", matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            printf("%f  ", matrix->data[linear_index(i, j, matrix->cols)]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(Matrix *matrix){
    free(matrix->data);
    free(matrix);
}

Matrix * matrix_cpy(Matrix *matrix){
    if(matrix == NULL){
        printf("Null pointer!");
        exit(EXIT_FAILURE);
    }
    if (matrix->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    Matrix *n_matrix = create_matrix(matrix->rows, matrix->cols);
    for(int i = 0; i < matrix->rows * matrix->cols; i++){
        n_matrix->data[i] = matrix->data[i];
    }
    return n_matrix;
    
}

int arg_max(Matrix *matrix){
    if(matrix == NULL){
        printf("Null pointer!");
        exit(EXIT_FAILURE);
    }
    if (matrix->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    if(matrix->cols != 1){
        printf("arg_max expects (M, 1) shaped matrix!");
        exit(EXIT_FAILURE);
    }
    float max = matrix->data[0];
    int max_idx = 0;
    for(int i = 1; i < matrix->rows; i++){
        if(matrix->data[i] > max){
            max = matrix->data[i];
            max_idx = i;
        }
    }
    return max_idx;
}

void print_shape(Matrix *matrix){
    printf("Shape of matrix is (%d, %d)\n", matrix->rows, matrix->cols);
}