# ifndef TSP_APPROXIMATE_H_
# define TSP_APPROXIMATE_H_
# include "util.h"
# include <math.h>
# include <queue>
struct Point {
    int idx;
    double x;
    double y;
    Point(int idx, double x, double y):idx(idx), x(x), y(y){}
};
/**
 * @brief comparison for priority queue, given index and distance, 
 * if distance is equal than set smaller index as higher priority.
 * rhs with higher priority.
 */
class Comparison {
  bool reverse;
public:
/**
 * @brief Construct a new Comparison object
 * 
 * @param revparam true for min heap; false for max heap
 */
  Comparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const std::pair<int, double>& lhs, const std::pair<int, double>& rhs) const
  {
    if (lhs.second == rhs.second) return (lhs.first > rhs.first);
    if (reverse)
        return (lhs.second > rhs.second);
    else
        return (lhs.second < rhs.second);
  }
};
/**
 * @brief approximately solve traveling salesman problem, hopefully accept a larger input size
 * example:
 * int main ()
{
    TSP_APPROXIMATE test;
    if (!ReadData("../data/_ae5a820392a02042f87e3b437876cf19_nn.txt", true, test))
        std::cout << "fail reading data!\n";
    std::cout.precision(10); // keep double precision
    std::cout << test.Greedy_TSP() << "\n";
    return 0;
}
 */
class TSP_APPROXIMATE {
private:
    int size;
    std::vector<Point> points;
    typedef std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, Comparison> heap;
public:
    /**
     * @brief  the first line in the test data can be adjusted to a smaller number n, so the algorithm 
     * only visit the first n cities. if n = 50, 1000, 5000, the result will be 2470, 48581, 188129, 
     * respectively. 
     * @param line 
     */
    void ProcessHeader (std::string& line) {
        this->size = std::stoi(line);
    }
    /**
     * @brief The first line indicates the number of cities. Each city is a point in the plane, 
     * and each subsequent line indicates the x- and y-coordinates of a single city.  
     * 
     * @param line
     */
    void ProcessLine (std::string& line) {
        std::istringstream ss(line);
        int i;
        double x, y;
        ss >> i >>  x >> y; 
        this->points.emplace_back(Point(i, x, y));
    }
    /**
     * @brief The distance between two cities is defined as the Euclidean distance --- that is,
     *  two cities at locations (x,y) and (z,w) have distance sqrt{(x−z)^2+(y−w)^2} between them
     *  
     * @param a 
     * @param b 
     * @return double square of euclidean distance between 2 points 
     */
    double square_distance(Point& a, Point& b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }
    /**
     * @brief given the points sorted by x coordinate, search in a circle region
     * for the nearest point, if there's a tie, return smaller index
     * @param visit indicate witch index were visit
     * @param src 
     * @return int index of city
     */
    int FindNearest(std::vector<bool>& visit, Point& src) {
        // search for west points (on the left side of src)
        heap left(Comparison(true));
        //std::cout << "\nleft add\n";
        for (int idx = src.idx; idx > 0; --idx) {
            if (visit[idx]) continue;
            auto dist = square_distance(src, this->points[idx - 1]);
            left.emplace(std::make_pair(idx, dist)); 
            //std::cout << "( " << idx << ", " << dist << " )\t"; 
            if (abs(this->points[idx - 1].x - src.x) > left.top().second) break;
        }
        // search for east points (on the right side of src)
        heap right(Comparison(true));
        //std::cout << "\nright add\n";
        for (int idx = src.idx; idx <= this->size; ++idx) {
            if (visit[idx]) continue;
            auto dist = square_distance(src, this->points[idx - 1]);
            right.emplace(std::make_pair(idx, dist)); 
            //std::cout << "( " << idx << ", " << dist << " )\t";
            if (abs(this->points[idx - 1].x - src.x) > right.top().second) break;
        }
        if (left.empty()) return right.top().first;
        if (right.empty()) return left.top().first;
        if (left.top().second == right.top().second) return std::min(left.top().first, right.top().first); 
        return (left.top().second < right.top().second) ? left.top().first : right.top().first;
    }
    /**
     * @brief from index 1, pick the nearest point as route of traveling salesman problem.
     * 
     * @return double distance of result route.
     */
    double Greedy_TSP () {
        auto src = this->points[0];
        std::vector<bool> visit(this->size + 1, false);
        std::vector<int> route;
        visit[src.idx] = true; // index 1
        route.emplace_back(src.idx);
        while (route.size() < this->size) {
            int next = FindNearest(visit, src);
            route.emplace_back(next);
            visit[next] = true;
            src = this->points[next - 1];
        }
        double ans = 0.0;
        auto cur = this->points[0];
        for (auto& idx:route) {
            ans += sqrt(square_distance(this->points[idx-1], cur));
            cur = this->points[idx-1];
        }
        ans += sqrt(square_distance(cur, this->points[0]));
        return ans;
    }
};
# endif /* TSP_APPROXIMATE_H_ */