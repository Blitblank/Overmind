
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
    
    Network network(1, 1);
    
    ReLu* relu = new ReLu();
    Layer inputLayer(1, 100, relu);
    Layer hiddenLayer(100, 100, relu);
    Layer outputLayer(100, 1, relu);

    network.addLayer(&inputLayer);
    network.addLayer(&hiddenLayer);
    network.addLayer(&outputLayer);

    std::vector<double> inputs;
    inputs.push_back(0.5);
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
