
#include "Network.hpp"

#include <iostream>

Network::Network(int _inputs, int _outputs) : n_inputs(_inputs), n_outputs(_outputs) {

}

void Network::train(double epochs, double learningRate) {

    for(int epoch = 0; epoch < epochs; epoch++) {
        double aggregateLoss = 0.0;
        int X_size = dataset->X.size();
        for(int i = 0; i < X_size; i++) {
            std::vector<double> output = forwardPass(dataset->X[i]);
            aggregateLoss += loss->calculate(output, dataset->Y[i]);
            backwardPass(output, dataset->Y[i], learningRate);
        }
        std::cout << "Current Epoch: " << epoch+1 << "  Mean Loss: " << (aggregateLoss/X_size) << std::endl;
        // TODO: live update progress bar
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
