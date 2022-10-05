#include "rational.h"

int main()
{
    CS170::Rational<int> const r1(1,2);
    CS170::Rational<int> const r2(1,3);
    r1 += r2;
}
