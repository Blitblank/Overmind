
#pragma once

#include<vector>

#include "Layer.hpp"
#include "Dataset.hpp"
#include "Loss.hpp"

class Network {

    public:

    Network(int _inputs, int _outputs);
    Network(std::string filename);
    ~Network() = default;

    void train(int epochs, double learningRate);
    std::vector<double> forwardPass(std::vector<double> inputs);
    void backwardPass(std::vector<double> yPredicted, std::vector<double> yTrue, double learningRate);
    void addLayer(Layer* layer);
    void setDataset(Dataset* _dataset);
    void setLoss(Loss* _loss) { loss = _loss; }

    void save(std::string filename);
    void load(std::string filename);
    void demonstrate(int n);

    private:

    std::vector<Layer*> layers;
    Dataset* dataset;
    Loss* loss;
    
    int n_inputs = 0;
    int n_outputs = 0;
    int n_layers = 0;
    double currentLoss = 1.0;
    long long trainingIterations = 0;

    const std::string dir = "../models/";

};
