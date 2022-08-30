# ifndef TSP_APPROXIMATE_H_
# define TSP_APPROXIMATE_H_
# include "util.h"
# include <math.h>
# include <unordered_set>
# include <queue>
struct Point {
    int idx;
    float x;
    float y;
    Point(int idx, float x, float y):idx(idx), x(x), y(y){}
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
  bool operator() (const std::pair<int, float>& lhs, const std::pair<int, float>& rhs) const
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
    std::cout << test.Greedy_TSP() << "\n";
    return 0;
}
 */
class TSP_APPROXIMATE {
private:
    int size;
    std::vector<Point> points;
    typedef std::priority_queue<std::pair<int, float>, std::vector<std::pair<int, float>>, Comparison> heap;
public:
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
        float x, y;
        ss >> i >>  x >> y; 
        this->points.emplace_back(Point(i, x, y));
    }
    /**
     * @brief The distance between two cities is defined as the Euclidean distance --- that is,
     *  two cities at locations (x,y) and (z,w) have distance sqrt{(x−z)^2+(y−w)^2} between them
     *  
     * @param a 
     * @param b 
     * @return float square of euclidean distance between 2 points 
     */
    float square_distance(Point& a, Point& b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }
    /**
     * @brief given the points sorted by x coordinate, search in a circle region
     * for the nearest point
     * @param route ignoring points already chosen
     * @param src 
     * @return int index of the nearest point
     */
    int FindNearest(std::unordered_set<int>& route, Point& src) {
        // search for west points (on the left side of src)
        heap left(Comparison(true));
        for (int idx = src.idx; idx > 0; --idx) {
            if (route.count(idx)) continue;
            auto dist = square_distance(src, this->points[idx - 1]);
            left.emplace(std::make_pair(idx, dist)); 
            if (abs(this->points[idx - 1].x - src.x) > left.top().second) break;
        }
        // search for east points (on the right side of src)
        heap right(Comparison(true));
        for (int idx = src.idx; idx <= this->size; ++idx) {
            if (route.count(idx)) continue;
            auto dist = square_distance(src, this->points[idx - 1]);
            right.emplace(std::make_pair(idx, dist)); 
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
        std::unordered_set<int> route;
        route.emplace(src.idx);
        while (route.size() < this->size) {
            int next = FindNearest(route, src);
            route.emplace(next);
            src = this->points[next - 1];
        }
        double ans = 0;
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