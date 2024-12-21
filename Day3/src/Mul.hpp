#pragma once
#include <vector>

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

private:
    std::vector<Pair<int>> m_pairs;
};