
#include "Activation.hpp"

#include <iostream>

Activation::Activation() {
    
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