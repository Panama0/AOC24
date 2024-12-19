#pragma once
#include <vector>

class Reports
{
public:
    using ReportStorage = std::vector<std::vector<int>>;

    void loadFromFile(const char* file);

    bool isSafeSimple(const std::vector<int>& report);
    void checkReports();

private:
    ReportStorage m_reports;
    ReportStorage m_unsafeReports;
    ReportStorage m_safeReports;
};