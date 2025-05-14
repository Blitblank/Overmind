
#pragma once

#include "Activation.hpp"

#include<vector>

class Layer {

    public:

    Layer(int _inputs, int _neurons, Activation* _activation);
    ~Layer() = default;

    std::vector<double> forward(std::vector<double> inputs); // pass inputs through. size of inpout/ouput vectors match the size of the layer
    void print(); // display weights and biases of the layer

    private:

    // number of
    int n_inputs = 0;
    int n_neurons = 0;

    std::vector<std::vector<double>> weights;
    std::vector<double> biases;

    Activation* activation;

};
