
#include "Activation.hpp"

#include <iostream>

Activation::Activation() {

}

double Activation::pass(double x) {
    return x;
}

double Activation::derivative(double x) {
    return 1.0;
}

Activation* Activation::fromID(int id) {
    switch (id) {
    case 0:
        return new Activation();
        break;
    case 1:
        return new ReLu();
        break;
    case 2:
        return new Sigmoid();
        break;
    default:
        return new Activation();
        break;
    }
}

double ReLu::pass(double x) {
    return (x > 0.0) ? x : 0.0;
}

double ReLu::derivative(double x) {
    return (x > 0.0) ? 1.0 : 0.0;
}

double Sigmoid::pass(double x) {
    return 1 / (1 + exp(-x));
}

double Sigmoid::derivative(double x) {
    double a = pass(x);
    return a * (1 - a);
}