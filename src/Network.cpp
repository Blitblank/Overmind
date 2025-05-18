
#include "Network.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>

Network::Network(int _inputs, int _outputs) : n_inputs(_inputs), n_outputs(_outputs) {

}

Network::Network(std::string filename) {
    load(filename);
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
        currentLoss = aggregateLoss/X_size;
        trainingIterations += X_size;

        std:: cout << "||  Mean Loss: " << currentLoss << std::endl;
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

void Network::save(std::string filename) {

    std::string path = dir + filename;
    std::fstream file;
    file.open(path.c_str(), std::ios::out);
    std::cout << "Saving Network to " << path << std::endl;

    // headers (all relevant neural network information)
    // number of layers, number of inputs, number of outputs, loss function id
    file << "Number of Layers,Number of Inputs,Number of Outputs,Loss Function ID,Current Loss,Iterations Trained" << std::endl;
    file << n_layers << "," << n_inputs << "," << n_outputs << "," << loss->getID() << "," << currentLoss << "," << trainingIterations << std::endl;

    // then start printing layers
    for(int i = 0; i < n_layers; i++) {
        layers[i]->save(&file, i+1);
    }
    file.close();
}

void Network::load(std::string filename) {

    layers.clear();
    std::string path = dir + filename;
    std::fstream file;
    file.open(path.c_str(), std::ios::in);
    std::cout << "Loading Network from " << path << "..."; 

    std::string line;
    std::getline(file, line);
    std::getline(file, line);
    std::vector<std::string> row;
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ',')) {
        row.push_back(cell);
    }
    n_layers = std::stoi(row[0]);
    n_inputs = std::stoi(row[1]);
    n_outputs = std::stoi(row[2]);
    currentLoss = std::stod(row[4]);
    trainingIterations = std::stoi(row[5]);

    loss = new Loss();
    loss = loss->fromID(std::stoi(row[3]));

    for(int i = 0; i < n_layers; i++) {
        Layer* layer = new Layer(&file);
        addLayer(layer);
        n_layers--; // because add layer adds 1 to n_layers so that its updated when done manually
    }
    std::cout << " Success." << std::endl;
}

void Network::demonstrate(int n) {

    std::default_random_engine generator(18);
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    std::cout << "\nNetwork Demo >> x" << n << std::endl;

    for(int i = 0; i < n; i++) {

        std::vector<double> inputs = { distribution(generator) };
        std::vector<double> outputs = forwardPass(inputs);

        std::cout << "Inputs: (";
        for(int i = 0; i < inputs.size(); i++) {
            std::cout << std::setw(12) << inputs[i];
            if(i != inputs.size() - 1) std::cout << ", "; 
        }
        std::cout << ")  Network Outputs: (";
        for(int i = 0; i < outputs.size(); i++) {
            std::cout << std::setw(12) << outputs[i];
            if(i != outputs.size() - 1) std::cout << ", "; 
        }
        std::cout << ")    Expected Outputs: (";
        std::cout << std::setw(12) << std::sin(inputs[0]) << ", ";
        std::cout << std::setw(12) << std::cos(inputs[0]) << ") " << std::endl;
    }
}