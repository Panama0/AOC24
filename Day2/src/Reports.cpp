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
                std::cout << item << ' ';
            }
            std::cout << '\n';
        }
    }
    std::cout << "The total safe reports is: "<< safeCount << '\n';
}

bool Reports::isSafe(std::vector<int>& report)
{
    size_t incCount{1};
    size_t decCount{1};

    bool failedDiff{false};
    int failedDiffCount{};
    int differance{};
    
    for(size_t i{1}; i < report.size(); i++)
    {
        if(report[i-1] < report[i])     // increasing
        {
            incCount++;
        }

        if(report[i-1] > report[i])     // decreasing
        {
            decCount++;
        }
        
        if(!failedDiff)
        {
            differance = std::abs(report[i-1] - report[i]);
        }
        else
        {
            differance = std::abs(report[i-2] - report[i]);
            failedDiff = false;
        }
        
        if((differance > 3 || differance == 0))
        {
            failedDiff = true;
            failedDiffCount++;

            if(failedDiffCount > 1)
            {
                return false;
            }
        }
    }


    
    if(incCount == report.size() || decCount == report.size())
    {
        return true;
    }
    else if (incCount == report.size() - 1 && decCount == 2)
    {
        return true;
    }
    else if (decCount == report.size() - 1 && incCount == 2)
    {
        return true;
    }
    
    return true;
}