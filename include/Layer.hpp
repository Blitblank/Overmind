
#pragma once

#include "Activation.hpp"

#include<vector>

class Layer {

    public:

    Layer(int _inputs, int _neurons, Activation* _activation);
    ~Layer() = default;

    std::vector<double> forward(std::vector<double> inputs); // pass inputs through. size of inpout/ouput vectors match the size of the layer
    std::vector<double> backward(std::vector<double> inputs, double learningRate); // backpropagation
    void print(); // display weights and biases of the layer

    private:

    std::vector<double> updateLayer(std::vector<double> dZ, double learningRate);

    // number of
    int n_inputs = 0;
    int n_neurons = 0;

    std::vector<std::vector<double>> weights;
    std::vector<double> biases;

    std::vector<double> currentInput;
    std::vector<double> currentZ;
    std::vector<double> currentOutput;

    Activation* activation;

};
