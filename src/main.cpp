#include "all-pairs_shortest-path.h"

int main ()
{
    AllPairsShortestPath test;
    if (!ReadData("../data/_6ff856efca965e8774eb18584754fd65_g3.txt", true, test))
        std::cout << "fail reading data.\n";
    std::cout<< test.ShortestShortestPath() << "\n";
    return 0;
}