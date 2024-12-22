#pragma once
#include <vector>
#include <string>

template<typename T>
struct Pair
{
    T first{};
    T second{};
};

class Mul
{
public:
    void parse(const char* file);
    void printProduct();
    
private:
    void getPairs(const std::vector<std::string>& matches);
    
    std::vector<Pair<int>> m_pairs;
};