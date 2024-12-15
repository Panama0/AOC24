#include "Parser.hpp"
#include <cstddef>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>
#include <system_error>

void Parser::populateLists(const char* path)
{
    std::ifstream in;

    in.open(path);
    
    std::string currentWord;
    for(int count{}; in >> currentWord; count++)
    {
        if(count % 2 == 0)      // is even
        {
            addToList(m_list1, std::stoi(currentWord));
        }
        else
        {
            addToList(m_list2, std::stoi(currentWord));
        }
    }
    in.close();
}

void Parser::addToList(List& list, const int value)
{
    if(list.empty())
    {
        list.push_back(value);
        return;
    }

    for(auto it = list.begin(); it != list.end(); it++)
    {
        if(*it < value)
        {
            list.emplace(it, value);
            return;
        }
    }
    // if this is the new largest value so far
    list.emplace_back(value);
}

void Parser::printDistance()
{
    int distance{};

    for (size_t i{}; i < m_list1.size(); i++)
    {
        distance += abs(m_list1[i] - m_list2[i]);
    }
    std::cout << distance;
}

void Parser::printSimScore()
{
    int simScore{};
    int appearances{};

    for (auto a : m_list1)
    {
        for(auto b : m_list2)
        {
            if(a == b)
            {
                appearances++;
            }
        }
        simScore += a * appearances;
        appearances = 0;
    }
    std::cout << simScore;
}