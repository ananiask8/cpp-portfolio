//
// Created by José Hilario on 10 Feb 2020.
//
#include <iostream>
#include <tic.h>
#include <typeinfo>

namespace readIn {
    template <typename T>
    void prompt() {
        T readIn;
        std::cout << "Please type a " << typeid(T).name() << " type: ";
        while (!(std::cin >> readIn)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "WRONG! Please type a " << typeid(T).name() << " type: ";
        }
    }
    int main() {
        prompt<bool>();
        prompt<char>();
        prompt<int>();
        prompt<double>();
        prompt<std::string>();
    }
}
