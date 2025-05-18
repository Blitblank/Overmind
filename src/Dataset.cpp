
#include "Dataset.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <string>

Dataset::Dataset() {
    
}

void Dataset::generateSin(int n) {

    std::default_random_engine generator(2); // keep seed constant if you want to test things
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    for(int i = 0; i < n; i++) {
        std::vector<double> x = { distribution(generator) }; // random x
        std::vector<double> y = { sin(x[0]), cos(x[0]) };

        X.push_back(x);
        Y.push_back(y);
    }
}

void Dataset::generateDataset(std::string filename, int n) {

    // rng
    std::default_random_engine generator(2); // keep seed constant if you want to test things
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    int xSize = 1; // x vector size
    int ySize = 2; // y vector size

    // create file
    std::fstream file;
    std::string path = dir + filename;

    std::cout << "Creating Dataset at " << path << ". Entries: " << n << ". (X length, Y length)=(" << xSize << ", " << ySize << ")...";

    file.open(path.c_str(), std::ios::out | std::ios::app);
    // header info: [x length, y length, n_lines]
    file << xSize << "," << ySize << "," << n << std::endl;

    for(int i = 0; i < n; i++) {

        std::vector<double> x = { distribution(generator) };
        std::vector<double> y = { sin(x[0]), cos(x[0]) };

        for(int j = 0; j < xSize; j++) {
            file << x[j] << ",";
        }
        file << ",";
        for(int j = 0; j < ySize; j++) {
            file << y[j] << ",";
        }
        file << std::endl;
    }
    file.close();
    std::cout << " Success." << std::endl;
}

void Dataset::loadDataset(std::string filename) {

    // read file
    std::fstream file;
    std::string path = dir + filename;
    file.open(path.c_str(), std::ios::in);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << path << std::endl;
    }

    std::cout << "Loading Dataset from " << path << "..."; 
    
    std::string line;
    int index = 0;
    int xSize = 0;
    int ySize = 0;
    int numEntries = 0;
    while (std::getline(file, line)) {

        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if(index == 0) {
            xSize = std::stoi(row[0]);
            ySize = std::stoi(row[1]);
            numEntries = std::stoi(row[2]);
        } else {
            std::vector<double> x;
            std::vector<double> y;
            for(int i = 0; i < xSize; i++) {
                x.push_back(std::stod(row[i]));
            }
            for(int i = 0; i < ySize; i++) {
                y.push_back(std::stod(row[i+xSize+1]));
            }
            X.push_back(x);
            Y.push_back(y);
        }
        index++;
    }

    file.close();

    std::cout << " Success. Entries Parsed: " << index-1 << ". (X length, Y length)=(" << xSize << ", " << ySize << ")" << std::endl; 

}


