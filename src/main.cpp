#include "count_split_inv.h"

int main ()
{
    CountSplitInv test;
    std::vector<int> v;
    //bool result = test.read_vector_data("../data/_bcb5c6658381416d19b01bfc1d3993b5_IntegerArray.txt", v);
    //if (!result) std::cout << "fail reading data!\n";
    v = {5,3,1,6,4,2};
    std::cout << test.count_split_inv(v) << "\n";
    return 0;
}