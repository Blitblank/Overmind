
#pragma once

#include<vector>

#include "Layer.hpp"
#include "Dataset.hpp"
#include "Loss.hpp"

class Network {

    public:

    Network(int _inputs, int _outputs);
    ~Network() = default;

    void train(double epochs, double learningRate);
    std::vector<double> forwardPass(std::vector<double> inputs);
    void backwardPass(std::vector<double> yPredicted, std::vector<double> yTrue, double learningRate);
    void addLayer(Layer* layer);
    void setDataset(Dataset* _dataset) { dataset = _dataset; }
    void setLoss(Loss* _loss) { loss = _loss; }

    private:

    std::vector<Layer*> layers;
    Dataset* dataset;
    Loss* loss;
    
    int n_inputs = 0;
    int n_outputs = 0;
    int n_layers = 0;

};
