
#include "Network.hpp"

#include <iostream>

Network::Network(int _inputs, int _outputs) : n_inputs(_inputs), n_outputs(_outputs) {

}

void Network::train() {

}

std::vector<double> Network::forwardPass(std::vector<double> inputs) {
    std::vector<double> current = inputs;
    for(int i = 0; i < n_layers; i++) {
        current = layers[i]->forward(current);
        for(int j = 0; j < current.size(); j++) {
            std::cout << "current: (" << j << ") = " << current[j] << std::endl;
        }
    }
    return current;
}

void Network::addLayer(Layer* layer) {
    layers.push_back(layer);
    n_layers++;
}
