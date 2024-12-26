#include <cstddef>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include <iostream>

namespace Types
{
    using Instructions = std::vector<std::pair<int, int>>;
    using Updates = std::vector<std::vector<int>>;
}

void parseIns(Types::Instructions& ins, std::fstream& fin)
{
    char ch;
    std::string firstWord;
    std::string secondWord;
    
    bool first{true};
    
    while(fin)
    {
        ch = fin.get();
        
        if(ch == '|')
        {
            first = false;
        }
        else if(ch == '\n')
        {
            if(first)       // signifies the start of the pages section
            {
                return;
            }
            
            first = true;
            
            ins.emplace_back(std::pair{stoi(firstWord), std::stoi(secondWord)});
            firstWord.clear();
            secondWord.clear();
        }
        else        // it is a valid character
        {
            if(first)
            {
                firstWord.push_back(ch);
            }
            else
            {
                secondWord.push_back(ch);
            }
        }
    }
}

void parseUpdates(Types::Updates& updates, std::fstream& fin)
{
    char ch;
    std::string word;
    std::vector<int> currentUpdate;
    
    while(fin)
    {
        ch = fin.get();
        
        if(ch == ',')
        {
            currentUpdate.emplace_back(std::stoi(word));
            word.clear();
        }
        else if(ch == '\n')
        {
            currentUpdate.emplace_back(std::stoi(word));
            updates.emplace_back(currentUpdate);
            currentUpdate.clear();
            word.clear();
        }
        else        // its a valid character
        {
            word.push_back(ch);
        }
    }
}

void parse(const char* file, Types::Instructions& instructions, Types::Updates& updatePages)
{
    std::fstream fin(file);
    
    parseIns(instructions, fin);
    parseUpdates(updatePages, fin);
}

bool checkSingleUpdate(const std::vector<int>& update, const Types::Instructions& ins)
{

    for(auto instruction : ins)
    {
        int i{};
        
        bool firstFound{false};
        bool secondFound{false};
        
        int firstIndex{};
        int secondIndex{};
        
        for(auto page : update)
        {
            
            if(page == instruction.first)
            {
                firstFound = true;
                firstIndex = i;
            }
            else if(page == instruction.second)
            {
                secondFound = true;
                secondIndex = i;
            }
            
            if(firstFound && secondFound)
            {
                if(firstIndex > secondIndex)
                {
                    return false;
                }
            }
            
            i++;
        }
    }
    // nothing failed
    return true;
}

Types::Updates checkUpdates(const Types::Instructions& ins, const Types::Updates& updates)
{
    Types::Updates correctUpdates;
    
    for(auto update : updates)      // loop through each update
    {
        if(checkSingleUpdate(update, ins))
        {
            correctUpdates.emplace_back(update);
        }
    }
    
    return correctUpdates;
}

void printMiddleSum(const Types::Updates& updates)
{
    int sum{};
    
    for(auto update : updates)
    {
        size_t midpoint{update.size() / 2};     // integer division woo
        sum += update[midpoint];
    }
    std::cout << "The midpoint sum was: " << sum << '\n';
}

int main()
{
    Types::Instructions instructions;
    Types::Updates updatePages;
    
    
    parse("../res/input", instructions, updatePages);
    Types::Updates correctUpdates = checkUpdates(instructions, updatePages);
    
    printMiddleSum(correctUpdates);
}