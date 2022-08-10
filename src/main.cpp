#include "Prims_minimum_spanning_tree.h"

int main ()
{
    PrimsMinimumSpanningTree test(INT32_MAX);
    Graph g;
    if(test.ReadGraph("../data/_d4f3531eac1d289525141e95a2fea52f_edges.txt", g));
        std::cout << "read data with " << g.size() << " elements\n";
    //printGraph(g);
    test.findMST(g, 1);
    std::cout << test.cost() << "\n";

    return 0;
}