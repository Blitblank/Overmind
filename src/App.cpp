
#include "App.hpp"

#include <iostream>

App::App() {
    std::cout << "App constructor" << std::endl;
}

void App::init() {
    std::cout << "App initializer" << std::endl;
}

void App::run() {
    std::cout << "App run" << std::endl;
}
