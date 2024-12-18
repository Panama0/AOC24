#include "Reports.hpp"
#include <cassert>
#include <vector>

int main()
{
    Reports reports;
    reports.loadFromFile("../res/input");

    std::vector<int> a {1, 2, 3};
    assert(reports.isSafe(a));

    std::vector<int> b {40, 56, 41, 42};
    assert(reports.isSafe(b));

    std::vector<int> c {40, 20, 41, 42};
    assert(reports.isSafe(c));

    std::vector<int> d {41, 40 ,41, 40};
    assert(!reports.isSafe(d));

    std::vector<int> e {41, 40 ,41, 42, 60};
    assert(!reports.isSafe(e));

    std::vector<int> f {10, 40 ,80, 1, 76};
    assert(!reports.isSafe(f));
    
    std::vector<int> g {10, 10 ,10, 1, 2};
    assert(!reports.isSafe(g));

    std::vector<int> h {33, 30 ,80, 1, 76};
    assert(!reports.isSafe(h));

    std::vector<int> i {14, 17, 20, 21, 24, 26, 27, 24};
    assert(reports.isSafe(i));

    std::vector<int> j {41,40,42,43};
    assert(reports.isSafe(j));

    std::vector<int> k {1,2,7,8,9};
    assert(!reports.isSafe(k));

    std::vector<int> l {9,8,7,2,1};
    assert(!reports.isSafe(l));


    reports.printSafeCount();
}