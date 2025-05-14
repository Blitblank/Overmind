
#include "Activation.hpp"

#include <iostream>

Activation::Activation() {
    std::cout << "Activation constructor" << std::endl;
}

double Activation::pass(double x) {
    return x;
}

double ReLu::pass(double x) {
    if(x <= 0.0) return 0.0;
    return x;
}

double Sigmoid::pass(double x) {
    return 1 / (1 + exp(-x));
}