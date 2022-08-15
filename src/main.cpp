#include "clustering.h"

int main ()
{
    Clustering test;
    if(ReadData("../data/_fe8d0202cd20a808db6a4d5d06be62f4_clustering1.txt", true, test))
        std::cout << "read data with " << test.GetEdgeSize() << " elements\n";
    std::cout << test.GreedyKruskalMST(4) << "\n";
    return 0;
}