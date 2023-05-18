#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

template <typename T>
void printShaOut(const std::vector<T> & data) {
    for (const auto c : data) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int) c << " ";
    }
    std::cout << std::endl;
}

std::vector<char> readBuffer(const std::string & filename);
