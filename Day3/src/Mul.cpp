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
    
    std::vector<std::string> instructions{};
    std::regex regex(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");
    
    for(std::sregex_iterator it(fileContents.begin(), fileContents.end(), regex); it != std::sregex_iterator(); it++)
    {
        std::smatch match{*it};
        instructions.emplace_back(match.str());
    }

    getPairs(instructions);
}

void Mul::getPairs(const std::vector<std::string>& instructions)
{
    bool enabled{true};
    
    for(auto instruction : instructions)
    {
        if(instruction == "do()")
        {
            enabled = true;
            continue;
        }
        else if(instruction == "don't()")
        {
            enabled = false;
            continue;
        }
        
        if(enabled)
        {
            size_t start{instruction.find('(') + 1};
            size_t middle{instruction.find(',')};
            size_t end{instruction.find(')') - 1};
            
            size_t firstLength{middle - start};
            size_t secondLengh{end - middle};
            
            int first{std::stoi(instruction.substr(start, firstLength))};
            int second{std::stoi(instruction.substr(middle + 1, secondLengh))};
            
            m_pairs.emplace_back(Pair<int>{first, second});
        }
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