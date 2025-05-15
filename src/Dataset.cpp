
#include "Dataset.hpp"

#include <iostream>
#include <random>

Dataset::Dataset() {
    
}

void Dataset::generateSin(int n) {

    std::default_random_engine generator(2); // keep seed constant if you want to test things
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    for(int i = 0; i < n; i++) {
        std::vector<double> x = { distribution(generator) }; // random x
        std::vector<double> y = { sin(x[0]), cos(x[0]) };

        X.push_back(x);
        Y.push_back(y);
    }

}