#include "lAlgebra.h"
#include <math.h>

typedef struct NeuralNet{
    int input_size;
    int num_neurons_hidden_layer;
    int output_size;
    double learning_rate;
    Matrix *weights_hidden_layer;
    Matrix *weights_output_layer;
}NeuralNet;

NeuralNet *create_neural_net(int input_size, int num_neurons_hidden_layer, int output_size, double learning_rate);
Matrix *forward(NeuralNet *nn, Matrix *input);
void free_neural_net(NeuralNet *nn);
double sigmoid(double input);
Matrix *apply_softmax(Matrix *matrix);
Matrix *apply_sigmoid(Matrix * matrix);
float cross_entropy_loss(Matrix *labels, Matrix *predictions);
Matrix *sigmoid_prime(Matrix *matrix);

