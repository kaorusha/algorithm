#include "quick_sort.h"

int main ()
{
    std::vector<int> v;
    bool result = ReadVectorData("../data/_32387ba40b36359a38625cbb397eee65_QuickSort.txt", v);
    if (!result) std::cout << "fail reading data!\n";
    QuickSort test;
    std::cout << test.Sort(v, 0, v.size()-1, test.median) << "\n ";
    return 0;
}