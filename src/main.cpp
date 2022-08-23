#include "optimal_BST.h"

int main ()
{
    OptimalBST test;
    std::vector<int> v = {20, 5, 17, 10, 20, 3, 25};
    std::cout << test.FindMinCost(v) << "\n";
    return 0;
}