# ifndef TSP_H_
# define TSP_H_
# include <math.h>
# include "util.h"

struct Point {
    float x;
    float y;
    Point(float x, float y):x(x), y(y){}
};
/**
 * @brief return the minimum distance of traveling salesman problem by dynamic programing approach.
 * assume n city with index 0 to n-1
 * example:
 * int main ()
{
    TravelingSalesmanProblem test;
    if (!ReadData("../data/_f702b2a7b43c0d64707f7ab1b4394754_tsp.txt", true, test))
        std::cout << "fail reading data!\n";
    std::cout << test.MinimumCost() << "\n";
    return 0;
}
 * reference: 
 https://cloud.tencent.com/developer/article/1103366
 https://www.youtube.com/watch?v=Q4zHb-Swzro
 */
class TravelingSalesmanProblem {
private:
    int size;
    float inf;
    std::vector<Point> points;
    
public:
    TravelingSalesmanProblem (float f):inf(f){}
    TravelingSalesmanProblem ():inf(1000000.0){}
    void ProcessHeader (std::string& line) {
        this->size = std::stoi(line);
    }
    /**
     * @brief The first line indicates the number of cities.  Each city is a point in the plane, 
     * and each subsequent line indicates the x- and y-coordinates of a single city.  
     * 
     * @param line 
     */
    void ProcessLine (std::string& line) {
        std::istringstream ss(line);
        float x, y;
        ss >> x >> y; 
        this->points.emplace_back(Point(x, y));
    }
    /**
     * @brief The distance between two cities is defined as the Euclidean distance --- that is,
     *  two cities at locations (x,y) and (z,w) have distance sqrt{(x−z)^2+(y−w)^2} between them
     * 
     * @param a 
     * @param b 
     * @return float 
     */
    float distance(Point& a, Point& b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
    /**
     * @brief the distances between index i, j is at [ i ][ j ]
     * 
     * @param p n size array representing city positions, index 1 to n
     * @return std::vector<std::vector<float>> (n+1) * (n+1) matrix, index corresponding to ith city, index 0 is unused
     */
    std::vector<std::vector<float>> FillDistMatrix (std::vector<Point>& p) {
        if (p.size() != this->size) {
            std::cout << "modify the size with input point vector size = " << p.size() << "\n";
            this->size = p.size();
        }
        // distance matrix
        std::vector<std::vector<float>> dist(this->size, std::vector<float>(this->size, this->inf));
        for (int i = 0; i < this->size; ++i) {
            for (int j = i; j < this->size; ++j) {
                if (i == j) dist[i][j] = 0.0;
                else {
                    dist[i][j] = distance(p[i], p[j]);
                    dist[j][i] = dist[i][j];
                }
            }
        }
        return dist;
    }
    float DP_TSP (std::vector<std::vector<float>>& c) {
        int subsets = (1 << (this->size)); // total 2^n subsets
        // Let A = 2-D array, indexed by subsets S ⊆ {1, 2, . . . , n} that contain 1 and 
        // destinations j ∈ {1, 2, . . . , n}
        std::vector<std::vector<float>> dp(subsets, std::vector<float>(this->size, this->inf));
        // Base case:
        // A[S, 1] = 0      if S = {1}
        // A[S, 1] = +∞     otherwise [no way to avoid visiting vertex (twice)]
        dp[1][0] = 0;
        // first index means subset: so 0 is empty, and 1 means only first city is in the subset
        // second index means destination, and 0 means 1st city
        for (int s = 1; s < subsets; ++s) {
            // For each set S ⊆ {1, 2, . . . , n} of size >= 2 that contains 1st city
            if (!(s & 1)) continue; 
            // For each j ∈ S, j != 1st city (index 0)
            for (int j = 1; j < this->size; ++j) {
                // A[S, j] = min (k ∈ S,k != j) {A[S − {j}, k] + c[k][j] }
                if (s & (1 << j)) continue; // city j has been considered 
                for (int k = 0; k < this->size; ++k) {
                    if ((s & (1 << k)) && k != j) {
                        dp[s | (1 << j)][j] = std::min(dp[s | (1 << j)][j], dp[s][k] + c[k][j]); //[same as recurrence] 
                        //std::cout << "s = " << s << "\tj = " << j << "\ts|j = " << (s | (1 << j)) << "\n";
                    }
                }
            }
        }
        // min cost from 1st city to j visiting everybody once + cost of final hop of tour
        float ans = this->inf;
        for (int j = 1; j < this->size; ++j) {
            ans = std::min(ans, dp[subsets - 1][j] + c[j][0]);
        }
        return ans;
    }

    auto MinimumCost() {
        auto c = FillDistMatrix(this->points);
        return DP_TSP(c);
    }
};
# endif /* TSP_H_ */