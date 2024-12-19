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

// bool Reports::isSafe(std::vector<int>& report)
// {
//     std::vector<int>::const_iterator prevIt{};

//     int failCount{0};

//     bool increasingPair{false};
//     bool decreasingPair{false};

//     //first loop for the order
//     for(auto it = report.begin(); it != report.end(); prevIt = it, it++)
//     {
//         if(it == report.begin())
//         {
//             // skip the first iteration of the loop
//             continue;
//         }

//         if(*prevIt < *it)     // increasing
//         {
//             increasingPair = true;

//             if(decreasingPair)
//             {
//                 report.erase(--it);
//                 failCount++;
//                 // it is now removed
//                 decreasingPair = false;
//             }
//         }

//         if(*prevIt > *it)     // decreasing
//         {
//             decreasingPair = true;

//             if(increasingPair)
//             {
//                 // have to decrement first as the value behind the it is the issue
//                 report.erase(--it);
//                 failCount++;
//                 // it is now removed
//                 decreasingPair = false;
//             }
//         }
//     }
//     if(failCount > 1)
//     {
//         return false;
//     }

//     //loop for the difference rule
//     for(auto it = report.begin(); it != report.end(); prevIt = it, it++)
//     {
//         if(it == report.begin())
//         {
//             // skip the first iteration of the loop
//             continue;
//         }

//         int differance{std::abs(*prevIt - *it)};
//         if(differance > 3 || differance == 0)
//         {
//             failCount++;
//             report.erase(it);
//             it--;
//         }
//     }

//     if(failCount > 1)
//     {
//         return false;
//     }


//     return true;
// }

// bool Reports::isIncreasing(const std::vector<int>& report)
// {
//     int i{};

//     int incCount{};
//     int decCount{};

//     int prevItem{};

//     for(auto item : report)
//     {
//         if(i++ == 0)
//         {
//             continue;
//             // skip the first iteration of the loop
//         }

//         if(item > prevItem)
//         {
//             incCount++;
//         }
//         else
//         {
//             decCount++;
//         }
//         prevItem = item;
//     }

//     if(incCount >= decCount)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

bool Reports::isSafeSimple(const std::vector<int>& report)
{
    size_t incCount{1};
    size_t decCount{1};
    
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
        int differance{std::abs(report[i-1] - report[i])};
        if(differance > 3 || differance == 0)
        {
            return false;
        }
    }
    
    if(incCount == report.size() || decCount == report.size())
    {
        return true;
    }
    // it is not safe at this point
    return false;
}

void Reports::checkReports()
{
    int safe{};

    for(auto report : m_reports)
    {
        if(isSafeSimple(report))
        {
            safe++;
            m_safeReports.emplace_back(report);
        }
        else
        {
            m_unsafeReports.emplace_back(report);
        }
    }

    for(auto report : m_unsafeReports)
    {
        for(size_t i{}; i < report.size(); i++)
        {
            std::vector<int> temp;
            for(size_t j{}; j < report.size(); j++)
            {
                if(j != i)  // try removing 1 by 1 until we hit the solution
                {
                    temp.emplace_back(report[j]);
                }
            }
            if(isSafeSimple(temp))
            {
                safe++;
                m_safeReports.emplace_back(report);
                break;
            }
        }
    }

    std::cout << "The number of safe reports was: " << safe << '\n';
}