#include "count_split_inv.h"

int main ()
{
    SplitInv test;
    std::vector<int> v;
    bool result = test.ReadVectorData("../data/_bcb5c6658381416d19b01bfc1d3993b5_IntegerArray.txt", v);
    if (!result) std::cout << "fail reading data!\n";
    std::cout << test.MergeSort(0,v.size()-1,v) << "\n";
    return 0;
}