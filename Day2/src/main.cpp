#include "Reports.hpp"
#include <cassert>
#include <vector>

int main()
{
    Reports reports;
    reports.loadFromFile("../res/input");
    reports.checkReports();
}