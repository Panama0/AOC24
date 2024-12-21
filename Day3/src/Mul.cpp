#include "Mul.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

void Mul::parse(const char* file)
{
    std::string fileContents;
    std::ifstream fin{file};

    while(fin)
    {
        fileContents.push_back(fin.get());
    }
    
    std::vector<size_t> matches{0};

    while(matches.back() != std::string::npos)
    {
        matches.emplace_back(fileContents.find("mul(", matches.back() + 1));
    }
    matches;

    // regex: /mul\(\d*,\d*\)/g
}