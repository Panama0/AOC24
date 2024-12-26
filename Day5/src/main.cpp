#include <fstream>
#include <string>
#include <utility>
#include <vector>

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

void parseUpdates(Types::Updates& updatePages, std::fstream& fin)
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
            updatePages.emplace_back(currentUpdate);
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

int main()
{
    Types::Instructions instructions;
    Types::Updates updatePages;
    
    
    parse("../res/input", instructions, updatePages);
}