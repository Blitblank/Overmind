
#include "Network.hpp"

#include <iostream>
#include <iomanip>

Network::Network(int _inputs, int _outputs) : n_inputs(_inputs), n_outputs(_outputs) {

}

void Network::train(int epochs, double learningRate) {

    std::cout << "Beginning Training Set of " << epochs << " epochs with learningRate = " << learningRate << "..." << std::endl;
    for(int epoch = 0; epoch < epochs; epoch++) {

        std::cout << "Current Epoch: " << std::left << std::setw(5) << epoch+1;

        double aggregateLoss = 0.0;
        int X_size = dataset->X.size();

        for(int i = 0; i < X_size; i++) {
            std::vector<double> output = forwardPass(dataset->X[i]);

            double dLoss = loss->calculate(output, dataset->Y[i]);
            if(dLoss != dLoss) throw std::invalid_argument("Loss NaN");
            aggregateLoss += dLoss;

            backwardPass(output, dataset->Y[i], learningRate);

            if(i % (X_size/100) == 0) std::cout << "=";
        }

        std:: cout << "||  Mean Loss: " << (aggregateLoss/X_size) << std::endl;
    }

}

std::vector<double> Network::forwardPass(std::vector<double> inputs) {
    std::vector<double> current = inputs;
    for(int i = 0; i < n_layers; i++) {
        current = layers[i]->forward(current);
    }
    return current;
}

void Network::backwardPass(std::vector<double> yPredicted, std::vector<double> yTrue, double learningRate) {
    std::vector<double> gradient = loss->gradient(yPredicted, yTrue);
    for(int i = n_layers-1; i >= 0; i--) {
        gradient = layers[i]->backward(gradient, learningRate);
    }
}

void Network::addLayer(Layer* layer) {
    layers.push_back(layer);
    n_layers++;
}

void Network::setDataset(Dataset* _dataset) {
    dataset = _dataset;
}
