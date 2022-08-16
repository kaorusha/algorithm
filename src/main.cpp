#include "clustering_big.h"

int main ()
{
    ClusteringBig test;
    if(!ReadData("../data/_fe8d0202cd20a808db6a4d5d06be62f4_clustering_big.txt", true, test))
        std::cout << "fail opening file";
    std::cout << "cluster num: " << test.MergeDistance() << "\n";
    return 0;
}