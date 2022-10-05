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

    // check "index" DOES NOT works in the LHS
    tc(0,2) = "this line should NOT compiler, it modifies const object";

    return 0;
}
