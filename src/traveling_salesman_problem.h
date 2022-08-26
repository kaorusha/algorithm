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
 * @brief in progress......
 * 
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
        // distance matrix starts at 1, and 0 is unused
        std::vector<std::vector<float>> dist(this->size + 1, std::vector<float>(this->size + 1, this->inf));
        for (int i = 1; i <= this->size; ++i) {
            for (int j = i; j <= this->size; ++j) {
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
        int subsets = (1 << (this->size + 1)); // total 2^(n+1) subsets
        // Let A = 2-D array, indexed by subsets S ⊆ {1, 2, . . . , n} that contain 1 and 
        // destinations j ∈ {1, 2, . . . , n}
        std::vector<std::vector<float>> dp(subsets, std::vector<float>(this->size + 1, this->inf));
        // Base case:
        // A[S, 1] = 0      if S = {1}
        // A[S, 1] = +∞     otherwise [no way to avoid visiting vertex (twice)]
        dp[1][1] = 0;
        for (int s = 2; s <= subsets; ++s) {
            for (int j = 1; j <= this->size; ++j) {
                dp[s][j] = recursive(dp, c, s, j);
            }
        }
        return 0.0;
    }

    float recursive(std::vector<std::vector<float>>& dp, std::vector<std::vector<float>>& c, int s, int k) {
        // empty subset, this is the last step, return the dist back to source index 1
        if (s == ((1 << k) | 3)) return c[k][1];

    }
    int MinimumCost() {
        auto c = FillDistMatrix(this->points);

        return 0;
    }
};
# endif /* TSP_H_ */