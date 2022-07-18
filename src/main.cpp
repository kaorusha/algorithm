#include <iostream>
#include "karatsuba.h"

int main ()
{
    std::string a = "3141592653589793238462643383279502884197169399375105820974944592";
    std::string b = "2718281828459045235360287471352662497757247093699959574966967627";
    Karatsuba calc(a,b);
    std::cout << calc.multiplication() << "\n";
    return 0;
}