#include "NeuralNet.h"
#include <string.h>

typedef struct MNISTDataset{
    Matrix **images;
    int *labels;
    int dataset_size;
}MNISTDataset;


MNISTDataset *parse_mnist(char *file_name, int num_images){
    FILE *file;
    file = fopen(file_name, "r");
    if(file == NULL){
        printf("Error opening file %s\n", file_name);
        exit(EXIT_FAILURE);
    }

    int image_size = 28 * 28;
    int label_size = 1;
    int MAXCHAR = 10000;

    MNISTDataset *dataset = (MNISTDataset *) malloc(sizeof(MNISTDataset));
    dataset->dataset_size = num_images;
    dataset->images = (Matrix **) malloc(sizeof(Matrix*) * num_images);
    dataset->labels = (int *) malloc(sizeof(int) * num_images);

    if(dataset == NULL || dataset->images == NULL || dataset->labels == NULL){
        printf("Memory Allocation Error !");
        exit(EXIT_FAILURE);
    }

    int parsed_sample_count = 0;
    char row[MAXCHAR];
    while(!feof(file)){
        if(parsed_sample_count >= num_images){
            break;
        }
        fgets(row, MAXCHAR, file);
        char *token = strtok(row, ",");
        dataset->images[parsed_sample_count] = create_matrix(image_size, 1);
        int read_char_count = 0;
        while(token != NULL){
            if(read_char_count == 0){
                dataset->labels[read_char_count] = atoi(token);
                printf("True Label %d \n", dataset->labels[read_char_count]);

            }
            else{
                dataset->images[parsed_sample_count]->data[read_char_count - 1] = (float)atoi(token) / 255.0;
            }
            token = strtok(NULL, ",");
            read_char_count++;
        }
        parsed_sample_count++;
        free(token);
    }
    fclose(file);
    return dataset;
}

void free_dataset(MNISTDataset *dataset){
    free(dataset->labels);
    for(int i = 0; i < dataset->dataset_size; i++){
        free_matrix(dataset->images[i]);
    }
    free(dataset);
}


double check_accuracy(MNISTDataset *val_dataset, NeuralNet *nn){
    double accuracy = 0.0f;
    for(int i = 0; i < val_dataset->dataset_size; i++){
        Matrix * predictions = forward(nn, val_dataset->images[i]);
        int predicted_label = arg_max(predictions);
        if (predicted_label == val_dataset->labels[i]){
            accuracy++;
        }
        free_matrix(predictions);
    }
    return accuracy / (double)val_dataset->dataset_size;
}

int main(int argc, char const *argv[]){
    int num_epochs = 5;
    int true_count = 0;
    MNISTDataset *dataset =  parse_mnist("./archive/mnist_train.csv", 20000);
    MNISTDataset *val_dataset = parse_mnist("./archive/mnist_test.csv", 1000);
    NeuralNet * nn = create_neural_net(784, 512, 10, 0.01);

    for(int epoch = 0; epoch < num_epochs; epoch++){
        printf("Training epoch %d \n", epoch);
        for(int i = 0; i < dataset->dataset_size; i++){
            //Feed Forward
            Matrix * hidden_output = dot_product(nn->weights_hidden_layer, dataset->images[i]);
            Matrix * hidden_outputs_activasion = apply_sigmoid(hidden_output);
            Matrix *final_outputs = dot_product(nn->weights_output_layer, hidden_outputs_activasion);
            Matrix *final_outputs_activasion = apply_sigmoid(final_outputs);


            Matrix *softmaxed_outputs = apply_softmax(final_outputs_activasion);
            int predicted_label = arg_max(softmaxed_outputs);

            if(predicted_label == dataset->labels[i]){
                true_count +=1;

            }
            //Calculate Loss
            Matrix *label = create_matrix(final_outputs->rows, final_outputs->cols);
            fill_matrix_const(label, 0);
            label->data[dataset->labels[i]] = 1;
            

            Matrix *output_errors = subtract_matrices(label, final_outputs_activasion);
            Matrix *transposed_mat = transpose(nn->weights_output_layer);
            Matrix* hidden_errors = dot_product(transposed_mat, output_errors);


            //Backpropagation

            //Output Layer
            Matrix * sigmoid_primed_mat = sigmoid_prime(final_outputs_activasion);
            Matrix* multiplied_mat = multiply_matrices(output_errors, sigmoid_primed_mat);
            transposed_mat = transpose(hidden_outputs_activasion);
            Matrix* dot_mat = dot_product(multiplied_mat, transposed_mat);
            Matrix* scaled_mat = scale(dot_mat, nn->learning_rate);
            Matrix * added_mat = add_matrices(nn->weights_output_layer, scaled_mat);

            free_matrix(nn->weights_output_layer);
            nn->weights_output_layer = added_mat;
            
            free_matrix(sigmoid_primed_mat);
            free_matrix(multiplied_mat);
            free_matrix(transposed_mat);
            free_matrix(dot_mat);
            free_matrix(scaled_mat);

            //Hidden Layer

            sigmoid_primed_mat = sigmoid_prime(hidden_outputs_activasion);
            multiplied_mat = multiply_matrices(hidden_errors, sigmoid_primed_mat);
            transposed_mat = transpose(dataset->images[i]);
            dot_mat = dot_product(multiplied_mat, transposed_mat);
            scaled_mat = scale(dot_mat, nn->learning_rate);
            added_mat = add_matrices(nn->weights_hidden_layer, scaled_mat);
            
            free_matrix(nn->weights_hidden_layer);
            nn->weights_hidden_layer = added_mat;

            free_matrix(sigmoid_primed_mat);
            free_matrix(multiplied_mat);
            free_matrix(transposed_mat);
            free_matrix(dot_mat);
            free_matrix(scaled_mat);

            // Free matrices
            free_matrix(hidden_output);
            free_matrix(hidden_outputs_activasion);
            free_matrix(final_outputs);
            free_matrix(final_outputs_activasion);
            free_matrix(output_errors);
            free_matrix(hidden_errors);
        }
        double accuracy = check_accuracy(val_dataset, nn);
        printf("Epoch %d validation accuracy %lf \n", epoch, accuracy);
    }
    free_neural_net(nn);
    free_dataset(dataset);
    free_dataset(val_dataset);
    return 0;
}
