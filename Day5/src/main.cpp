#include <cstddef>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "Timing.hpp"

namespace Types
{
    using Instructions = std::vector<std::pair<int, int>>;
    using Updates = std::vector<std::vector<int>>;
    
    struct FailedInstruction
    {
        int first{};
        int second{};
        
        int firstIndex{};
        int secondIndex{};
    };
    
    struct UpdateVailidity
    {
        bool valid{true};
        std::vector<FailedInstruction> failedInstructions;
        
        operator bool()const { return valid; };
    };
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

Types::UpdateVailidity checkSingleUpdate(const std::vector<int>& update, const Types::Instructions& ins)
{
    Types::UpdateVailidity result;
    
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
                    result.valid = false;
                    
                    Types::FailedInstruction failData{instruction.first, instruction.second, firstIndex, secondIndex};
                    
                    result.failedInstructions.emplace_back(failData);
                }
                break;
            }
            i++;
        }
    }
    // nothing failed
    return result;
}

std::vector<int> fixUpdate(const std::vector<int>& update, const Types::UpdateVailidity& failInfo)
{
    struct MoveInfo
    {
        int page{};
        int offset{};
    };
    std::vector<MoveInfo> moves;
    
    for(auto failedIns : failInfo.failedInstructions)
    {
        bool ff{false};
        bool sf{false};
        
        for(auto moveIt = moves.begin(); moveIt != moves.end(); moveIt++)
        {
            if(moveIt->page == failedIns.first)
            {
                moveIt->offset++;
                ff = true;
            }
            else if((*moveIt).page == failedIns.second)
            {
                moveIt->offset--;
                sf = true;
            }
            if(ff && sf) {break;}
        }
        
        if(!ff)
        {
            moves.emplace_back(MoveInfo{failedIns.first, 1});
        }
        
        if(!sf)
        {
            moves.emplace_back(MoveInfo{failedIns.second, -1});
        }
    }
    
    // correct the update
    std::vector<int> fixedUpdate{update};
    
    for(auto move : moves)
    {
        int i{};
        for(auto page : update)
        {
            if(page == move.page)
            {
                fixedUpdate[i - move.offset] = page;
            }
            i++;
        }
    }
    
    return fixedUpdate;
}

Types::Updates checkUpdates(const Types::Instructions& ins, const Types::Updates& updates, bool fix = false)
{
    Types::Updates updatesOut;
    
    for(auto update : updates)      // loop through each update
    {
        if(Types::UpdateVailidity failData = checkSingleUpdate(update, ins))
        {
            if(!fix)
            {
                updatesOut.emplace_back(update);
            }
        }
        else
        {
            updatesOut.emplace_back(fixUpdate(update, failData));
        } 
    }
    
    return updatesOut;
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
    Timing::start();
    Types::Instructions instructions;
    Types::Updates updatePages;
    
    
    parse("../res/input", instructions, updatePages);
    //Types::Updates correctUpdates = checkUpdates(instructions, updatePages);
    
    Types::Updates fixedUpdates = checkUpdates(instructions, updatePages, true);
    
    printMiddleSum(fixedUpdates);
    Timing::end();
}