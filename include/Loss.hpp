
#pragma once

#include<vector>
class Loss {

    public:

    Loss();
    ~Loss() = default;

    virtual double calculate(std::vector<double> yPredicted, std::vector<double> yTrue);
    virtual std::vector<double> gradient(std::vector<double> yPredicted, std::vector<double> yTrue);
    virtual int getID() { return 0; }
    Loss* fromID(int id);

    private:

};

class MeanSquaredError : public Loss {

    public:

    double calculate(std::vector<double> yPredicted, std::vector<double> yTrue) override;
    std::vector<double> gradient(std::vector<double> yPredicted, std::vector<double> yTrue) override;
    int getID() override { return 1; }

    private:

};