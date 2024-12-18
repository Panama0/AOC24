#include "Reports.hpp"
#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

void Reports::loadFromFile(const char* file)
{
    std::fstream in;
    in.open(file);

    char tok[2]{};
    int charCount{};

    std::vector<int> currentReport;

    while (in)
    {
        char ch;
        in.get(ch);

        if(in.eof())
        {
            in.close();
            break;
        }
        
        if(ch == ' ' || ch == '\n')     //token or report over, add the token
        {
            int number = std::stoi(tok);
            currentReport.emplace_back(number);
            charCount = 0;
            // this is not ideal
            tok[1] = '\000';
        }
        else        //token continues
        {
            tok[charCount] = ch;
            charCount++;
        }

        if (ch == '\n')    // end of the report
        {
            m_reports.emplace_back(currentReport);
            currentReport = {};
            charCount = 0;
        }
        assert(charCount < 3);


    }
}

void Reports::printSafeCount()
{
    int safeCount{};
    for(auto report : m_reports)
    {
        if(isSafe(report))
        {
            safeCount++;
            
            for(auto item : report)
            {
                std::cout << item << ',';
            }
            std::cout << '\n';
        }
    }
    std::cout << "The total safe reports is: "<< safeCount << '\n';
}

bool Reports::isSafe(std::vector<int>& report)
{
    std::vector<int>::const_iterator prevIt{};

    int failCount{0};

    bool increasingPair{false};
    bool decreasingPair{false};

    //first loop for the order
    for(auto it = report.begin(); it != report.end(); prevIt = it, it++)
    {
        if(it == report.begin())
        {
            // skip the first iteration of the loop
            continue;
        }

        if(*prevIt < *it)     // increasing
        {
            increasingPair = true;

            if(decreasingPair)
            {
                report.erase(--it);
                failCount++;
                // it is now removed
                decreasingPair = false;
            }
        }

        if(*prevIt > *it)     // decreasing
        {
            decreasingPair = true;

            if(increasingPair)
            {
                // have to decrement first for decreasing as the value behind the it is the issue
                report.erase(--it);
                failCount++;
                // it is now removed
                decreasingPair = false;
            }
        }
    }
    if(failCount > 1)
    {
        return false;
    }

    //loop for the difference rule
    for(auto it = report.begin(); it != report.end(); prevIt = it, it++)
    {
        if(it == report.begin())
        {
            // skip the first iteration of the loop
            continue;
        }

        int differance{std::abs(*prevIt - *it)};
        if(differance > 3 || differance == 0)
        {
            failCount++;
            report.erase(it);
            it--;
        }
    }

    if(failCount > 1)
    {
        return false;
    }


    return true;
}