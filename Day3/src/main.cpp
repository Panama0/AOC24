#include "Mul.hpp"
#include "Timing.hpp"

int main()
{
    Timing::start();
    Mul mul;
    mul.parse("../res/input");
    Timing::end();
}