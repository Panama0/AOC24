#include <cassert>
#include <cstddef>
#include <string_view>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

void parse(const char* file, std::vector<std::string>& output)
{
    std::fstream fin(file);
    
    std::string line;
    
    while(fin >> line)
    {
        output.emplace_back(line);
    }
}

bool checkWord(std::string_view input, std::string_view searchString)
{
    for(size_t i{},count{}; i < searchString.size(); i++)
    {
        if(input[i] == searchString[i])
        {
            count++;
            if(count == searchString.size())
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    assert(false);      // something has gone wrong
    return false;
}

int searchP1(const std::vector<std::string>& input, std::string_view searchStr)
{
    std::string reverseSearchStr;
    for(auto it = searchStr.rbegin(); it != searchStr.rend(); it++)
    {
        reverseSearchStr.push_back(*it);
    }
    
    int wordCount{};
    
    size_t searchStrSize{searchStr.size()};
    size_t boardWidth{input.front().size()};
    size_t boardHeight{input.size()};
    
    std::string currentWord;
    
    for(size_t y{}; y < boardHeight; y++)
    {
        for(size_t x{}; x < boardWidth; x++)
        {
            // ---horizontal---
            
            // build up current word
            for(size_t i{}; i < searchStrSize && x <= boardWidth - searchStrSize; i++)
            {
                currentWord.push_back(input[y][x+i]);
            }
            
            if(checkWord(currentWord, searchStr) || checkWord(currentWord, reverseSearchStr))
            {
                wordCount++;
            }
            currentWord.clear();
            
            // ---vertical---
            
            // build up current word
            for(size_t i{}; i < searchStrSize && y <= boardHeight - searchStrSize; i++)
            {
                currentWord.push_back(input[y+i][x]);
            }
            
            if(checkWord(currentWord, searchStr) || checkWord(currentWord, reverseSearchStr))
            {
                wordCount++;
            }
            currentWord.clear();
            
            // ---diagonal right---
            
            // build up the current word
            //? maybe we change these x and y checks to comparing to a bounds?
            //? bounds would have the board width pre removed
            
            for(size_t i{}; i < searchStrSize && x <= boardWidth - searchStrSize && y <= boardHeight - searchStrSize; i++)
            {
                currentWord.push_back(input[y+i][x+i]);
            }
            
            if(checkWord(currentWord, searchStr) || checkWord(currentWord, reverseSearchStr))
            {
                wordCount++;
            }
            currentWord.clear();
            
            // ---diagonal left---
            
            // build up the current word
            for(size_t i{}; i < searchStrSize && x >= searchStrSize - 1 && y <= boardHeight - searchStrSize; i++)
            {
                currentWord.push_back(input[y+i][x-i]);
            }
            
            if(checkWord(currentWord, searchStr) || checkWord(currentWord, reverseSearchStr))
            {
                wordCount++;
            }
            currentWord.clear();
        }
    }
    return wordCount;
}

int searchP2(const std::vector<std::string>& input, std::string_view searchStr)
{
    std::string reverseSearchStr;
    for(auto it = searchStr.rbegin(); it != searchStr.rend(); it++)
    {
        reverseSearchStr.push_back(*it);
    }
    
    int wordCount{};
    
    size_t searchStrSize{searchStr.size()};
    size_t boardWidth{input.front().size()};
    size_t boardHeight{input.size()};
    
    std::string currentWordDown;
    std::string currentWordUp;
    
    for(size_t y{}; y < boardHeight; y++)
    {
        for(size_t x{}; x < boardWidth; x++)
        {
            // build up current words
            for(size_t i{}; i < searchStrSize && x <= boardWidth - searchStrSize && y <= boardHeight - searchStrSize; i++)
            {
                currentWordDown.push_back(input[y+i][x+i]);
                currentWordUp.push_back(input[(y-i)+searchStrSize - 1][x+i]);
            }
            
            if(checkWord(currentWordUp, searchStr) || checkWord(currentWordUp, reverseSearchStr))
            {
                if(checkWord(currentWordDown, searchStr) || checkWord(currentWordDown, reverseSearchStr))
                {
                    wordCount++;
                }
            }
        }
    }
    
    return wordCount;
}

int main()
{
    std::vector<std::string> searchData;
    std::string searchString{"MAS"};
    
    parse("../res/input", searchData);
    //searchP1(searchData, searchString);
    int wordCount{searchP2(searchData, searchString)};
    
    std::cout << "The number of occurances of " << searchString << " was: "
        << wordCount << '\n';
}