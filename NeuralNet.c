#include "NeuralNet.h"


NeuralNet *create_neural_net(int input_size, int num_neurons_hidden_layer, int output_size, double learning_rate){
    NeuralNet *nn = (NeuralNet*) malloc(sizeof(NeuralNet));
    if(nn == NULL){
        printf("Memory Allocation Error !");
        exit(EXIT_FAILURE);
    }
    nn->input_size = input_size;
    nn->num_neurons_hidden_layer = num_neurons_hidden_layer;
    nn->output_size = output_size;
    nn->learning_rate = learning_rate;

    nn->weights_hidden_layer = create_matrix(num_neurons_hidden_layer, input_size);
    fill_matrix_rand(nn->weights_hidden_layer, -1, 1);

    nn->weights_output_layer = create_matrix(output_size, num_neurons_hidden_layer);
    fill_matrix_rand(nn->weights_output_layer, -1, 1);

    return nn;
}

double sigmoid(double input){
    return 1.0 / (1 + exp(-1 * input)); 
}

Matrix *apply_sigmoid(Matrix * matrix){
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
        n_matrix->data[i] = sigmoid(matrix->data[i]);
    }
    return n_matrix;
}

Matrix *apply_softmax(Matrix *matrix){
    if(matrix == NULL){
        printf("Null pointer!");
        exit(EXIT_FAILURE);
    }
    if (matrix->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    double total = 0;
    for(int i = 0; i < matrix->rows * matrix->cols; i++){
        total += exp(matrix->data[i]);
    }
    Matrix *n_matrix = create_matrix(matrix->rows, matrix->cols);
    for(int i = 0; i < matrix->rows * matrix->cols; i++){
        n_matrix->data[i] = exp(matrix->data[i]) / total;
    }
    return n_matrix;
}

Matrix *sigmoid_prime(Matrix *matrix){
    Matrix *ones = create_matrix(matrix->rows, matrix->cols);
    fill_matrix_const(ones, 1.0);
    Matrix *subtracted = subtract_matrices(ones, matrix);
    Matrix *multiplied = multiply_matrices(matrix, subtracted);
    free_matrix(ones);
    free_matrix(subtracted);
    return multiplied;
}

float cross_entropy_loss(Matrix *labels, Matrix *predictions){
    if(labels == NULL || predictions == NULL){
        printf("Null pointer!");
        exit(EXIT_FAILURE);
    }
    if(labels->data == NULL || predictions->data == NULL){
        printf("Matrix mem is not initialized!");
        exit(EXIT_FAILURE);
    }
    if(labels->cols != 1 != predictions->rows != 1){
        printf("cross_entropy_loss expects (M, 1) shaped matrix!");
        exit(EXIT_FAILURE);
    }
    if(labels->rows != predictions->rows){
        printf("cross_entropy_loss expects same shaped matrices !");
        exit(EXIT_FAILURE);
    }
    Matrix * softmax_predictions = apply_softmax(predictions);
    float loss = 0.0f;
    for(int i = 0; i < labels->rows; i++){
        loss = loss + (-1 * (double) labels->data[i] * log((double)predictions->data[i]));
    }
    return loss;
}

Matrix *forward(NeuralNet *nn, Matrix *input){
    Matrix *hidden_outputs = dot_product(nn->weights_hidden_layer, input);
    Matrix *activasion_hidden_outputs = apply_sigmoid(hidden_outputs);

    Matrix *final_outputs = dot_product(nn->weights_output_layer, activasion_hidden_outputs);
    Matrix *activasion_final_outputs = apply_sigmoid(final_outputs);

    Matrix *softmax_outs = apply_softmax(activasion_final_outputs);

    free_matrix(hidden_outputs);
    free_matrix(activasion_hidden_outputs);
    free_matrix(final_outputs);
    free_matrix(activasion_final_outputs);

    return softmax_outs;
}

void train_neural_net(NeuralNet *nn, Matrix *inputs, Matrix* outputs){
    return;
}

void free_neural_net(NeuralNet *nn){
    free_matrix(nn->weights_hidden_layer);
    free_matrix(nn->weights_output_layer);
    free(nn);
}
