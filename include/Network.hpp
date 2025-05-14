
#pragma once

#include<vector>

#include "Layer.hpp"
#include "Dataset.hpp"

class Network {

    public:

    Network(int _inputs, int _outputs);
    ~Network() = default;

    void train();
    std::vector<double> forwardPass(std::vector<double> inputs);
    void addLayer(Layer* layer);

    private:

    std::vector<Layer*> layers;
    Dataset* dataset;
    
    int n_inputs = 0;
    int n_outputs = 0;
    int n_layers = 0;

};
