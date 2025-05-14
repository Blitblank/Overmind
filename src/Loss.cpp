
#include "Loss.hpp"

#include <iostream>

Loss::Loss() {
    std::cout << "Loss constructor" << std::endl;
}

double Loss::calculate(std::vector<double> yPredicted, std::vector<double> yTrue) {

    // default mean absolute error
    int size = yPredicted.size();
    if (size != yTrue.size()) {
        throw std::invalid_argument("vector size mismatch");
    }

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += std::abs(yPredicted[i] - yTrue[i]);
    }

    return sum / yPredicted.size();
}


double MeanSquaredError::calculate(std::vector<double> yPredicted, std::vector<double> yTrue) {

    int size = yPredicted.size();
    if (size != yTrue.size()) {
        throw std::invalid_argument("vector size mismatch");
    }

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        double diff = yPredicted[i] - yTrue[i];
        sum += diff * diff;
    }

    return sum / yPredicted.size();
}