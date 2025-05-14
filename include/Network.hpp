
#pragma once

#include<vector>

#include "Layer.hpp"
#include "Dataset.hpp"

class Network {

    public:

    Network();
    ~Network() = default;

    void train();
    std::vector<double> forwardPass(std::vector<double> inputs);
    void addLayer(Layer layer);

    private:

    std::vector<Layer> layers;
    Dataset dataset;
    
};
