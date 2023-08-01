#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Matrix{
    int rows;
    int cols;
    float *data;
}Matrix;

int linear_index(int x, int y, int cols);
double rand_double(double min, double max);

Matrix *create_matrix(int rows, int cols);
Matrix *transpose(Matrix* matrix);
Matrix *matrix_cpy(Matrix *matrix);

void fill_matrix_const(Matrix *matrix, double n);
void fill_matrix_rand(Matrix *matrix, double min, double max);
void display_matrix(Matrix *matrix);
void free_matrix(Matrix *matrix);
void print_shape(Matrix *matrix);

int arg_max(Matrix *matrix);
