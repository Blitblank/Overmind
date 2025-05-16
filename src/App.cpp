
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
    
    // construct model
    int n_inputs = 1;
    int n_outputs = 2;
    int hiddenNeurons_1 = 20;
    int hiddenNeurons_2 = 20;
    Network network(n_inputs, n_outputs);
    
    Loss* loss = new MeanSquaredError();
    Layer inputLayer(n_inputs, hiddenNeurons_1, new ReLu());
    Layer hiddenLayer(hiddenNeurons_1, hiddenNeurons_2, new ReLu());
    Layer outputLayer(hiddenNeurons_2, n_outputs, new Activation());

    network.addLayer(&inputLayer);
    network.addLayer(&hiddenLayer);
    network.addLayer(&outputLayer);
    network.setLoss(loss);
    std::cout << "Network Created." << std::endl;

    // create dataset
    Dataset dataset;
    //dataset.generateSin(100);
    //dataset.generateDataset("../datasets/sin_cos_005.csv", 1000000);
    dataset.loadDataset("../datasets/sin_cos_005.csv");
    network.setDataset(&dataset);

    // train model
    // i do different sets here with different leanring rates but eventually i might have an algo that has adaptive leanring rate
    network.train(20, 0.01);
    //network.train(5, 0.006);
    //network.train(5, 0.004);

    // demonstrate model
    std::vector<double> inputs = { 0.1422 };
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
