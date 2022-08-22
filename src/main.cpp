#include "knapsack.h"

int main ()
{
    Knapsack test;
    if(!ReadData("../data/_6dfda29c18c77fd14511ba8964c2e265_knapsack_big.txt", true, test))
        std::cout << "fail opening file";
    std::cout << test.MaxValue() << "\n";
    return 0;
}