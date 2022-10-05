#include "table.h"
#include <iostream>

int main()
{
    CS170::Table t(2,3);

    t(0,0) = "aaaa";
    t(0,1) = "bbbbbbbb";
    t(0,2) = "cccc";
    t(1,0) = "12";
    t(1,1) = "345678";
    t(1,2) = "90";

    // create a const table
    CS170::Table const tc( t );

    // check "index" works
    std::cout << tc(0,2) << std::endl;

    // check copy from const object works
    CS170::Table t2( tc );

    // check assignmnet from const object works
    t = tc;

    // check we can print a const object
    std::cout << tc << std::endl;

    // both operators should allow const arguments in either arg1 or arg2
    CS170::Table r1 = tc + tc;
    CS170::Table r2 = tc * tc;
    return 0;
}
