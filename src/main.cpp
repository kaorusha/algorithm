#include "two_sum.h"
#include "util.h"

int main ()
{
    std::vector<long int> v;
    if(ReadVectorData("../data/_6ec67df2804ff4b58ab21c12edcb21f8_algo1-programming_prob-2sum.txt", v))
        std::cout << "read data with " << v.size() << " elements\n";
    TwoSum test;
    std::cout << test.NumWithinRange(-10000, 10000, v) << std::endl;
    return 0;
}