
#include "App.hpp"

#include <iostream>
#include "Network.hpp"

App::App() {
    std::cout << "App constructor" << std::endl;
}

void App::init() {
    std::cout << "App initializer" << std::endl;
}

void App::run() {
    
    int n_inputs = 2;
    int n_outputs = 2;
    int hiddenNeurons_1 = 100;
    int hiddenNeurons_2 = 100;
    Network network(n_inputs, n_outputs);
    
    Activation* activation = new Sigmoid();
    Layer inputLayer(n_inputs, hiddenNeurons_1, activation);
    Layer hiddenLayer(hiddenNeurons_1, hiddenNeurons_2, activation); //
    Layer outputLayer(hiddenNeurons_2, n_outputs, activation);

    network.addLayer(&inputLayer);
    network.addLayer(&hiddenLayer);
    network.addLayer(&outputLayer);
    //inputLayer.print();
    //hiddenLayer.print();
    //outputLayer.print();

    std::vector<double> inputs;
    for(int i = 0; i < n_inputs; i++) {
        inputs.push_back(0.2);
    }
    std::vector<double> outputs = network.forwardPass(inputs);

    std::cout << "\nNetwork Input: " << std::endl;
    for(int i = 0; i < inputs.size(); i++) {
        std::cout << inputs[i];
        if(i != inputs.size() - 1) std::cout << ", "; 
    }
    std::cout << "\nNetwork Output: " << std::endl;
    for(int i = 0; i < outputs.size(); i++) {
        std::cout << outputs[i];
        if(i != outputs.size() - 1) std::cout << ", "; 
    }
    std::cout << std::endl;
    
}
