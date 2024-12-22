#include "Mul.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

void Mul::parse(const char* file)
{
    std::string fileContents;
    std::ifstream fin{file};

    while(fin)
    {
        fileContents.push_back(fin.get());
    }

    // this regex part is very slowwww
    // only takes 1ms in release tho lul
    
    std::vector<std::string> matches{};
    std::regex regex(R"(mul\((\d+),(\d+)\))");
    
    for(std::sregex_iterator it(fileContents.begin(), fileContents.end(), regex); it != std::sregex_iterator(); it++)
    {
        std::smatch match{*it};
        matches.emplace_back(match.str());
    }

    getPairs(matches);
}

void Mul::getPairs(const std::vector<std::string>& matches)
{
    for(auto match : matches)
    {
        size_t start{match.find('(') + 1};
        size_t middle{match.find(',')};
        size_t end{match.find(')') - 1};
        
        size_t firstLength{middle - start};
        size_t secondLengh{end - middle};
        
        int first{std::stoi(match.substr(start, firstLength))};
        int second{std::stoi(match.substr(middle + 1, secondLengh))};
        
        m_pairs.emplace_back(Pair<int>{first, second});
    }
}

void Mul::printProduct()
{
    int total{};
    for(auto pair : m_pairs)
    {
        total += pair.first * pair.second;
    }
    std::cout << "The product of all pairs is: " << total << '\n';
}