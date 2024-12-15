#pragma once

#include <vector>

class Parser
{
public:
    using List = std::vector<int>;
    
    void populateLists(const char* path);
    void addToList(List& list, const int value);

    //probably will need a larger type, we will see
    void printDistance();
    // this is quite brute force, i'm sure theres a better way

    // could count how many occurances each list item has when we add them into
    // the list, thefore only looping once
    void printSimScore();

private:

    List m_list1;
    List m_list2;
};