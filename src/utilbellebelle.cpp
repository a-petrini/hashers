#include "utilbellebelle.hpp"

#include <iostream>
#include <fstream>

std::vector<char> readBuffer(const std::string & filename) {
    std::fstream file;
    file.open(filename, std::fstream::in);
    file.seekp(0, std::ios::end);
    size_t eofOffset = file.tellp();
    std::vector<char> filebuffer(eofOffset);
    file.seekp(0, std::ios::beg);
    file.read(filebuffer.data(), eofOffset);
    file.close();
    return filebuffer;
}