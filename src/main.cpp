#include "greedy_scheduling.h"
#include "util.h"

int main ()
{
    std::vector<std::pair<int,int>> v;
    GreedyScheduling test;
    if(test.ReadWeightLength("../data/_642c2ce8f3abe387bdff636d708cdb26_jobs.txt", v))
        std::cout << "read data with " << v.size() << " elements\n";
    test.SortByDifference(v);
    std::cout << "sort by difference completion time = "<< test.CompletionTime(v) << std::endl;
    test.SortByRatio(v);
    std::cout << "sort by ratio completion time = "<< test.CompletionTime(v) << std::endl;
    return 0;
}