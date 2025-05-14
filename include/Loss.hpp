
#pragma once

#include<vector>
class Loss {

    public:

    Loss();
    ~Loss() = default;

    virtual double calculate(std::vector<double> yPredicted, std::vector<double> yTrue);

    private:

};

class MeanSquaredError : public Loss {

    public:

    double calculate(std::vector<double> yPredicted, std::vector<double> yTrue) override;

    private:

};