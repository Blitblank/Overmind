
#pragma once

class Activation {

    public:

    Activation();
    ~Activation() = default;

    virtual double pass(double x); // default activation returns f(x) = x

    private:

};

class ReLu : Activation {
    public:
    double pass(double x);

    private:
};

class Sigmoid : Activation {
    public:
    double pass(double x);

    private:
};
