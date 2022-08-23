# ifndef OPTIMAL_BST_H_
# define OPTIMAL_BST_H_
# include "util.h"
/**
 * @brief given an array of nodes with its frequency, return the minimum overall search cost
 * example:
 * int main ()
{
    OptimalBST test;
    std::vector<int> v = {20, 5, 17, 10, 20, 3, 25};
    std::cout << test.FindMinCost(v) << "\n";
    return 0;
}
 */
class OptimalBST {
public:
    OptimalBST () {}
    /**
     * @brief find minimum search cost of the binary search tree. complexity O(n^3),
     * can be further optimized to O(n^2)
     * @param v the array of frequency (multiplied 100 to get integer)
     * @return int minimum cost 
     */
    int FindMinCost(std::vector<int>& v) {
        int n = v.size();
        std::vector<std::vector<int>> dp( n + 1, std::vector<int>(n + 1, 0));
        std::vector<std::vector<int>> root( n + 1, std::vector<int>(n + 1, 0));
        for (int j = 1; j <= n; ++j) {
            for (int i = 0; i < n; ++i) { 
                if (i + j > n) continue;
                // pick minimum cost
                int min = INT32_MAX;
                int r;
                int w = 0;
                // std::cout << "dp[ " << i << " ][ " << i+j << " ] = min {";
                for (int k = i; k < i + j; ++k) {
                    // std::cout << "c( " << i << ", " << k << ") + c( " << k+1 << ", " << i+j << "),\t";
                    int cost = dp[i][k] + dp[k+1][i+j];
                    if ( cost < min) {
                        min = cost;
                        r = k + 1;
                    }
                    if (k > i) w += v[k-1];
                }
                w += v[ i + j - 1 ];
                dp[i][i+j] = min + w;
                // std::cout << "} + w( " << i << " , " << i + j << ") = " << min << " + " << w << " = " << dp[i][i+j] << "\n";
                root[i][i+j] = r;
            }
        }
        return dp[0][n];
    }
};
# endif /* OPTIMAL_BST_H_ */