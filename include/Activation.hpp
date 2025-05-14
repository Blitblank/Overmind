
#pragma once

class Activation {

    public:

    Activation();
    ~Activation() = default;

    virtual double pass(double x); // default activation returns f(x) = x

    private:

};

class ReLu : public Activation {
    public:
    double pass(double x) override;

    private:
};

class Sigmoid : public Activation {
    public:
    double pass(double x) override;

    private:
};
