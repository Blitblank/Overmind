
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
    int hiddenNeurons_1 = 40;
    int hiddenNeurons_2 = 40;
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
    //dataset.generateSin(10000); // generates a brand new dataset
    //dataset.generateDataset("sin_cos_005.csv", 1000000); // generates a new dataset with n iterations and saves it in a csv file
    dataset.loadDataset("sin_cos_005.csv"); // guys this one probably loads a dataset
    //network.setDataset(&dataset); // and when you make a dataset you have to link it to the network

    // load a model and train it
    Network loadedNetwork("updated_model_001.csv"); // load a model from a csv file
    loadedNetwork.setDataset(&dataset); // attatch a dataset to the model for training
    loadedNetwork.train(10, 0.01); // train for n epochs with a certain leanring rate 
    loadedNetwork.save("updated_model_001.csv"); // save the new model. using the same file will overwrite it

    // demonstrate model
    std::vector<double> inputs = { 0.1422 };
    std::vector<double> outputs = loadedNetwork.forwardPass(inputs);

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
