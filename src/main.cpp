#include "karger_min_cut.h"

int main ()
{
    Graph graph;
    KargerMinCut test;
    bool result = test.ReadGraphData("../data/_f370cd8b4d3482c940e4a57f489a200b_kargerMinCut.txt", graph); 
    if (!result) std::cout << "fail reading data!\n";
    std::cout << test.CountMinCut(graph) << "\n";
    return 0;
}