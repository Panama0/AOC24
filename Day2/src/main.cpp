#include "Reports.hpp"

int main()
{
    Reports reports;
    reports.loadFromFile("../res/inputd");
    reports.printSafeCount();
}