#include "Parser.hpp"

int main()
{
    Parser parser;
    parser.populateLists("../res/input");
    parser.printSimScore();
}