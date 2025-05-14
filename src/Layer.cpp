
#include "Layer.hpp"

#include <iostream>
#include <stdexcept>

Layer::Layer(int _inputs, int _neurons, Activation* _activation) : n_inputs(_inputs), n_neurons(_neurons), activation(_activation) {

    // initialize size of vectors
    weights = std::vector<std::vector<double>>(n_inputs, std::vector<double>(n_neurons, 0.1057)); // this is ugly
    biases = std::vector<double>(n_neurons, 0.183);

}

std::vector<double> Layer::forward(std::vector<double> inputs) {

    // ensure matching vector sizes
    if(inputs.size() != n_inputs) {
        throw std::invalid_argument("input vector invalid size");
    }

    std::vector<double> output = std::vector<double>(n_neurons);

    // dot product each row of weights with the inputs and add biases
    for (int i = 0; i < n_neurons; i++) {
        output[i] = biases[i];
        for (int j = 0; j < n_inputs; j++) {
            output[i] += inputs[j] * weights[j][i];
        }
        // run through activation function
        output[i] = activation->pass(output[i]);
    }

    return output;
}

void Layer::print() {

    std::cout << "\nLAYER WEIGHTS & BIASES ======" << std::endl;
    std::cout << "  Weights" << std::endl;
    for(int i = 0; i < n_inputs; i++) {
        for(int j = 0; j < n_neurons; i++) {
            std::cout << weights[i][j];
            if(j != n_neurons - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "  Biases" << std::endl;
    for(int i = 0; i < n_neurons; i++) {
        std::cout << biases[i];
        if(i != n_neurons - 1) std::cout << ", ";
        std::cout << std::endl;
    }
}