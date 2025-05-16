
#include "Loss.hpp"

#include <iostream>

Loss::Loss() {

}

double Loss::calculate(std::vector<double> yPredicted, std::vector<double> yTrue) {

    // default mean absolute error
    int size = yPredicted.size();
    if (size != yTrue.size()) {
        throw std::invalid_argument("vector size mismatch");
    }

    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += std::abs(yPredicted[i] - yTrue[i]);
    }

    return sum / yPredicted.size();
}


std::vector<double> Loss::gradient(std::vector<double> yPredicted, std::vector<double> yTrue) {

    // default mean absolute error
    int size = yPredicted.size();
    if (size != yTrue.size()) {
        throw std::invalid_argument("vector size mismatch");
    }

    std::vector<double> gradient(size);
    for (int i = 0; i < size; i++) {
        gradient[i] = 1.0 / size;
    }

    return gradient;
}


double MeanSquaredError::calculate(std::vector<double> yPredicted, std::vector<double> yTrue) {

    int size = yPredicted.size();
    if (size != yTrue.size()) {
        throw std::invalid_argument("vector size mismatch");
    }

    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        double diff = yPredicted[i] - yTrue[i];
        sum += diff * diff;
    }

    double meanLoss = sum / yPredicted.size();
    return meanLoss;
}

std::vector<double> MeanSquaredError::gradient(std::vector<double> yPredicted, std::vector<double> yTrue) {

    int size = yPredicted.size();
    if (size != yTrue.size()) {
        throw std::invalid_argument("vector size mismatch");
    }

    std::vector<double> gradient(size);
    for (int i = 0; i < size; i++) {
        gradient[i] = 2.0 * (yPredicted[i] - yTrue[i]) / size;
    }

    return gradient;
}