#include "traveling_salesman_problem_approximate.h"

int main ()
{
    TSP_APPROXIMATE test;
    if (!ReadData("../data/greedy_tsp.txt", true, test))
        std::cout << "fail reading data!\n";
    std::cout << test.Greedy_TSP() << "\n";
    return 0;
}