
#pragma once

class Activation {

    public:

    Activation();
    ~Activation() = default;

    virtual double pass(double x); // default activation returns f(x) = x
    virtual double derivative(double x);
    virtual int getID() { return 0; }
    Activation* fromID(int id);

    private:

};

class ReLu : public Activation {
    public:
    double pass(double x) override;
    double derivative(double x) override;
    int getID() override { return 1; }

    private:
};

class Sigmoid : public Activation {
    public:
    double pass(double x) override;
    double derivative(double x) override;
    int getID() override { return 2; }

    private:
};
