#include "Reports.hpp"

int main()
{
    Reports reports;
    reports.loadFromFile("../res/input");
    reports.checkReports();
}