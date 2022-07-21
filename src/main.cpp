#include "count_split_inv.h"
#include "util.h"

int main ()
{
    std::vector<int> v;
    bool result = ReadVectorData("../data/_bcb5c6658381416d19b01bfc1d3993b5_IntegerArray.txt", v);
    if (!result) std::cout << "fail reading data!\n";
    
    return 0;
}