#include "dynamic_programing.h"

int main ()
{
    DynamicPrograming test;
    if(!ReadData("../data/_790eb8b186eefb5b63d0bf38b5096873_mwis.txt", true, test))
        std::cout << "fail opening file";
    std::vector<int> v = {1, 2, 3, 4, 17, 117, 517, 97};
    test.PrintIndex(v);
    return 0;
}