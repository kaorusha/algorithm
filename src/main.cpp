#include "traveling_salesman_problem.h"

int main ()
{
    TravelingSalesmanProblem test;
    if (!ReadData("../data/_f702b2a7b43c0d64707f7ab1b4394754_tsp.txt", true, test))
        std::cout << "fail reading data!\n";
    //std::cout << test.MinimumCost();
    return 0;
}