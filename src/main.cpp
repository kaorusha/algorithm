#include "2sat.h"

int main ()
{
    TwoSAT test;
    const std::string file_name = "../data/2sat/_02c1945398be467219866ee1c3294d2d_2sat";
    for (int i = 1; i <= 6; ++i) {
        std::cout << test.Satisfiable(file_name + std::to_string(i) + ".txt");
    }
    std::cout << "\n";
    return 0;
}