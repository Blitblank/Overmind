
#pragma once

#include<vector>
#include<string>

// right now im testing this network on a very simple dataset but it will eventually be able to accept multiple kinds
class Dataset {

    public:

    Dataset();
    ~Dataset() = default;
    
    void generateSin(int n);
    void loadDataset(std::string filename);
    void generateDataset(std::string filename, int n);

    std::vector<std::vector<double>> X;
    std::vector<std::vector<double>> Y;

    private:

};
