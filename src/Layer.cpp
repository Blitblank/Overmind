
#include "Layer.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <random>

Layer::Layer(int _inputs, int _neurons, Activation* _activation) : n_inputs(_inputs), n_neurons(_neurons), activation(_activation) {

    std::default_random_engine generator(13); // keep seed constant if you want to test things
    std::uniform_real_distribution<double> distribution(-0.1, 0.1);

    // initialize vectors
    weights = std::vector<std::vector<double>>(n_inputs, std::vector<double>(n_neurons)); // this is ugly
    biases = std::vector<double>(n_neurons);

    for (int i = 0; i < n_inputs; i++) {
        for (int j = 0; j < n_neurons; j++) {
            weights[i][j] = distribution(generator);
            biases[j] = distribution(generator);
        }
    }
}

Layer::Layer(std::fstream* file){
    load(file);
}

std::vector<double> Layer::forward(std::vector<double> inputs) {

    // ensure matching vector sizes
    if(inputs.size() != n_inputs) {
        throw std::invalid_argument("input vector invalid size");
    }

    currentInput = inputs;
    currentZ = std::vector<double>(n_neurons);
    currentOutput = std::vector<double>(n_neurons);

    // dot product each row of weights with the inputs and add biases
    for (int i = 0; i < n_neurons; i++) {
        currentZ[i] = biases[i];
        for (int j = 0; j < n_inputs; j++) {
            currentZ[i] += inputs[j] * weights[j][i];
        }
        // run through activation function
        currentOutput[i] = activation->pass(currentZ[i]);
    }

    return currentOutput;
}

std::vector<double> Layer::backward(std::vector<double> dOutputs, double learningRate) {

    std::vector<double> dZ(n_neurons);
    for(int i = 0; i < n_neurons; i++) {
        dZ[i] = dOutputs[i] * activation->derivative(currentZ[i]);
    }
    return updateLayer(dZ, learningRate);
}

std::vector<double> Layer::updateLayer(std::vector<double> dZ, double learningRate) {

    std::vector<double> dCurrent(n_inputs, 0.0);

    for(int i = 0; i < n_neurons; i++) {
        for(int j = 0; j < n_inputs; j++) {
            double dWeight = currentInput[j] * dZ[i]; // chain rule garbage
            weights[j][i] += (-1.0)*learningRate * dWeight;
            dCurrent[j] += weights[j][i] * dZ[i];
        }
        biases[i] += (-1.0)*learningRate * dZ[i];
    }

    return dCurrent;
}

void Layer::print() {

    std::cout << "\nLAYER WEIGHTS & BIASES ======" << std::endl;
    std::cout << "  Weights" << std::endl;
    for(int i = 0; i < n_inputs; i++) {
        for(int j = 0; j < n_neurons; j++) {
            std::cout << weights[i][j];
            if(j != n_neurons-1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n  Biases" << std::endl;
    for(int i = 0; i < n_neurons; i++) {
        std::cout << biases[i];
        if(i != n_neurons - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void Layer::save(std::fstream* file, int index) {

    // header: layer index, n_inputs, n_neurons(outputs), activationID
    *file << std::endl;
    *file << "Layer Index,Number of Inputs,Number of Neurons,Activation Function ID" << std::endl;
    *file << index << "," << n_inputs << "," << n_neurons << "," << activation->getID() << std::endl;

    *file << "Weights" << std::endl;
    for (int i = 0; i < n_inputs; ++i) {
        for (int j = 0; j < n_neurons; ++j) {
            *file << weights[i][j];
            if (j < n_neurons - 1) *file << ",";
        }
        *file << std::endl;
    }

    *file << "Biases" << std::endl;
    for (int j = 0; j < n_neurons; ++j) {
        *file << biases[j];
        if (j < n_neurons - 1) *file << ",";
    }
    *file << std::endl;

}

int Layer::load(std::fstream* file) {


    std::string line;
    for(int i = 0; i < 3; i++) std::getline(*file, line); // have to get through some junk

    std::vector<std::string> row;
    std::stringstream ss(line);
    std::string cell;

    // header info
    while (std::getline(ss, cell, ',')) {
        row.push_back(cell);
    }
    
    int layerIndex = std::stoi(row[0]);
    n_inputs = std::stoi(row[1]);
    n_neurons = std::stoi(row[2]);
    int activationID = std::stoi(row[3]);
    activation = new Activation();
    activation = activation->fromID(activationID);

    weights.resize(n_inputs, std::vector<double>(n_neurons));
    biases.resize(n_neurons);

    // weights
    std::getline(*file, line); // skip a line because of header
    for (int i = 0; i < n_inputs; i++) {
        std::getline(*file, line);
        std::istringstream row(line);
        for (int j = 0; j < n_neurons; ++j) {
            std::getline(row, cell, ',');
            weights[i][j] = std::stod(cell);
        }
    }

    // biases
    std::getline(*file, line);
    std::getline(*file, line); // skip again
    std::istringstream biasRow(line);
    for (int i = 0; i < n_neurons; i++) {
        std::getline(biasRow, cell, ',');
        biases[i] = std::stod(cell);
    }
    
    return layerIndex;
}
