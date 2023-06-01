#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

// ANSI console command for text coloring
#ifdef __unix
#define TXT_BICYA "\033[96;1m"
#define TXT_BIPRP "\033[95;1m"
#define TXT_BIBLU "\033[94;1m"
#define TXT_BIYLW "\033[93;1m"
#define TXT_BIGRN "\033[92;1m"
#define TXT_BIRED "\033[91;1m"
#define TXT_BIBLK "\033[90;1m"
#define TXT_NORML "\033[0m"
#else
#define TXT_BICYA ""
#define TXT_BIPRP ""
#define TXT_BIBLU ""
#define TXT_BIYLW ""
#define TXT_BIGRN ""
#define TXT_BIRED ""
#define TXT_NORML ""
#endif

template <typename T>
void printShaOut(const std::vector<T> & data) {
    for (const auto c : data) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int) c << " ";
    }
    std::cout << std::endl;
}
