#include "scc.h"

int main ()
{
    Graph graph;
    Graph graph_rev;
    SCC test(9);
    const std::string file = "../data/test1_9_33300.txt"; // node num = 875714
    if (!test.ReadGraphData(file, graph)) std::cout << "fail reading data!\n";
    if (!test.ReadGraphData(file, graph_rev, true)) std::cout << "fail reading data!\n";        
    test.findSCC(graph, graph_rev);
    return 0;
}