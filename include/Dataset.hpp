
#pragma once

#include<vector>

// right now im testing this network on a very simple dataset but it will eventually be able to accept multiple kinds
class Dataset {

    public:

    Dataset();
    ~Dataset() = default;

    struct Point {
        double x;
        double y;
    };
    

    void generateSin(int n);

    private:

    std::vector<Point> data;

};
