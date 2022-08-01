#include "kosaraju.h"

int main ()
{
    Graph graph;
    Graph graph_rev;
    Kosaraju test(875714);
    const std::string file = "../data/_410e934e6553ac56409b2cb7096a44aa_SCC.txt"; // node num = 875714
    if (!test.ReadGraphData(file, graph)) std::cout << "fail reading data!\n";
    if (!test.ReadGraphData(file, graph_rev, true)) std::cout << "fail reading data!\n";        
    test.findSCC(graph, graph_rev);
    return 0;
}