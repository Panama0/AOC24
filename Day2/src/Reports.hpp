#pragma once
#include <vector>

class Reports
{
public:
    using ReportStorage = std::vector<std::vector<int>>;

    void loadFromFile(const char* file);
    void printSafeCount();

    bool isSafe(const std::vector<int>& report);

private:
    ReportStorage m_reports;
};