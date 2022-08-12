#include "Prims_minimum_spanning_tree.h"

int main ()
{
    PrimsMinimumSpanningTree test(INT32_MAX);
    if(ReadData("../data/_d4f3531eac1d289525141e95a2fea52f_edges.txt", true, test));
        std::cout << "read data with " << test.GetVertexSize() << " elements\n";
    test.findMST(1);
    std::cout << test.cost() << "\n";

    return 0;
}