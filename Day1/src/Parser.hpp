#pragma once

#include <vector>

class Parser
{
public:
    using List = std::vector<int>;
    
    void populateLists(const char* path);
    void addToList(List& list, const int value);

    //probably will need a larger type, we will see
    int printDistance();

private:

    List m_list1;
    List m_list2;
};