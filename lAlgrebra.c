#include "lAlgebra.h"


Matrix *multiply_matrices(Matrix *m1, Matrix*m2){
    if(m1 == NULL || m2 == NULL){
        printf("Null pointer !");
        exit(EXIT_FAILURE);
    }
    if(m1->data == NULL || m2->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }

    if(m1->rows == m2->rows && m1->cols == m2->cols){
        Matrix *n_matrix = create_matrix(m1->rows, m1->cols);
        for(int i =0; i< m1->rows * m1->cols; i++){
            n_matrix->data[i] = m1->data[i] * m2->data[i];
        }
        return n_matrix;
    }
    else{
        printf("Dimension mistmatch in multiplication !");
        exit(EXIT_FAILURE);
    }
}

Matrix *add_matrices(Matrix *m1, Matrix *m2){
    if(m1 == NULL || m2 == NULL){
    printf("Null pointer !");
    exit(EXIT_FAILURE);
    }
    if(m1->data == NULL || m2->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }

    if(m1->rows == m2->rows && m1->cols == m2->cols){
        Matrix *n_matrix = create_matrix(m1->rows, m1->cols);
        for(int i =0; i< m1->rows * m1->cols; i++){
            n_matrix->data[i] = m1->data[i] + m2->data[i];
        }
        return n_matrix;
    }
    else{
        printf("Dimension mistmatch in add !");
        exit(EXIT_FAILURE);
    }
}

Matrix *subtract_matrices(Matrix *m1, Matrix *m2){
    if(m1 == NULL || m2 == NULL){
        printf("Null pointer !");
        exit(EXIT_FAILURE);
    }
    if(m1->data == NULL || m2->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }

    if(m1->rows == m2->rows && m1->cols == m2->cols){
        Matrix *n_matrix = create_matrix(m1->rows, m1->cols);
        for(int i =0; i< m1->rows * m1->cols; i++){
            n_matrix->data[i] = m1->data[i] - m2->data[i];
        }
        return n_matrix;
    }
    else{
        printf("Dimension mistmatch in subtract !");
        exit(EXIT_FAILURE);
    }
}

Matrix *scale(Matrix *matrix, double n){
    if(matrix == NULL){
        printf("Null pointer!");
        exit(EXIT_FAILURE);
    }
    if (matrix->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    Matrix *n_matrix = matrix_cpy(matrix);
    for(int i = 0; i < matrix->rows * matrix->cols; i++){
        n_matrix->data[i] *= n;
    }
    return n_matrix;
}

Matrix *add_scalar(Matrix *matrix, double n){
    if(matrix == NULL){
        printf("Null pointer!");
        exit(EXIT_FAILURE);
    }
    if (matrix->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    Matrix *n_matrix = matrix_cpy(matrix);
    for(int i = 0; i < matrix->rows * matrix->cols; i++){
        n_matrix->data[i] += n;
    }
    return n_matrix;
}


Matrix *dot_product(Matrix *m1, Matrix *m2){
    if(m1 == NULL || m2 == NULL){
        printf("Null pointer !");
        exit(EXIT_FAILURE);
    }
    if(m1->data == NULL || m2->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    if(m1->cols == m2->rows){
        Matrix * n_matrix = create_matrix(m1->rows, m2->cols);
        for(int i = 0; i < m1->rows; i++){
            for(int j = 0; j < m2->cols; j++){
                double sum = 0.0f;
                for(int k = 0; k < m2->rows; k++){
                    sum += m1->data[linear_index(i, k, m1->cols)] * m2->data[linear_index(k, j, m2->cols)];
                }
                n_matrix->data[linear_index(i, j, n_matrix->cols)] = sum;
            }
            
        }
        return n_matrix;
    }    
    else{
        printf("Dimension mistmatch in dot product !\n");
        printf("Matrix 1 dimensions are (%d, %d)\n", m1->rows, m1->cols);
        printf("Matrix 2 dimensions are (%d, %d)\n", m2->rows, m2->cols);

        exit(EXIT_FAILURE);
    }
}