#include "dijkstra_shortest_path.h"

int main ()
{
    DijkstraShortestPath test(200, 1000000);
    test.readGraphData("../data/_dcf1d02570e57d23ab526b1e33ba6f12_dijkstraData.txt");
    //test.printGraph();
    test.shortestPath(1);
    int order[] = {7,37,59,82,99,115,133,165,188,197}; // some interested goal vertex
    test.printDist();
    return 0;
}