#include "traveling_salesman_problem_approximate.h"

int main ()
{
    TSP_APPROXIMATE test;
    if (!ReadData("../data/_ae5a820392a02042f87e3b437876cf19_nn.txt", true, test))
        std::cout << "fail reading data!\n";
    std::cout.precision(10); // keep double precision
    std::cout << test.Greedy_TSP() << "\n";
    return 0;
}