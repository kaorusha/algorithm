#include "median_maintenance.h"
#include "util.h"

int main ()
{
    MediumMaintenance test;
    std::vector<int> v;
    if (!ReadVectorData("../data/_6ec67df2804ff4b58ab21c12edcb21f8_Median.txt", v))
        std::cout << "fail reading data\n";
    int ans = 0;
    for (auto& i:v) {
        auto m = test.update(i);
        ans += m;
    }
    std::cout << ans << "\n";
}