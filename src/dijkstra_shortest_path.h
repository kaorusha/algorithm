# ifndef DIJKSTRA_H_
# define DIJKSTRA_H_
# include <queue>
# include <sstream>
# include <fstream>
# include <iostream>
# include <algorithm>
/**
 * @brief comparison for priority queue to pop the smallest dist vertex
 * 
 */
class PairComparison {
    bool reverse;
public:
  PairComparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const std::pair<int,int>& lhs, const std::pair<int,int>& rhs) const
  {
    if (reverse) return (lhs.second < rhs.second);
    else return (lhs.second > rhs.second);
  }
};
/**
 * @brief find the smallest distance for from the source vertex to other vertices
 * example:
 * int main ()
{
    DijkstraShortestPath test(200, 1000000);
    test.readGraphData("../data/_dcf1d02570e57d23ab526b1e33ba6f12_dijkstraData.txt");
    //test.printGraph();
    test.shortestPath(1);
    int order[] = {7,37,59,82,99,115,133,165,188,197}; // some interested goal vertex
    test.printDist();
    return 0;
}
 */
class DijkstraShortestPath {
private:
    int vertex_num;
    int inf_dist;
    typedef std::vector<std::vector<std::pair<int, int>>> Graph;
    Graph graph;
    std::vector<int> dist;
    std::vector<bool> visit;
public:
/**
 * @brief Construct a new Dijkstra Shortest Path object
 * 
 * @param n the largest vertex label
 * @param dist when the vertex is unreachable from source, use this value
 */
    DijkstraShortestPath(int n, int dist): vertex_num(n), inf_dist(dist) {}
/**
 * @brief graph data represent each line means label followed by its neighbors
 * represented as pair {adjacent vertex label, distance}.
 * 
 * @param file_name 
 * @return true 
 * @return false 
 */
    inline bool readGraphData (const std::string& file_name) {
        std::ifstream is(file_name.c_str(), std::ifstream::in);
        // Return if we can't open the file
        if (!is) {
            std::cout << "fail reading data from file.\n";
            return false;
        }

        // Declare single line of file
        std::string line;

        // prepare graph space
        graph.resize(vertex_num + 1);
        // Run over each single line:
        while (std::getline(is, line)) {
            std::replace(line.begin(), line.end(), ',', ' ');
            std::istringstream ss(line);
            int idx;
            int vertex, distance;
            ss >> idx;
            if (idx > vertex_num) {
                std::cout << "index number is larger than initialized vertex number.\n";
                return false;
            }
            while (ss >> vertex >> distance) {
                auto adj = std::make_pair(vertex, distance);
                graph[idx].emplace_back(adj);
            }
        }
        is.close();
        return true;
    }
    void printGraph() {
        for (int i = 0; i < graph.size(); ++i) {
            std::cout << i << "\t";
            for (auto& adj:graph[i]) {
                std::cout << adj.first << "," << adj.second << "\t";
            }
            std::cout << "\n";
        }
    }
/**
 * @brief find the distance from source to other vertices
 * 
 * @param source vertex label 
 */
    void shortestPath(int source) {
        if (source > vertex_num) return;
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, PairComparison> pq;
        dist.resize(vertex_num+1, inf_dist);
        visit.resize(vertex_num+1, false);
        pq.push(std::make_pair(source, 0));
        dist[source] = 0;
        while (!pq.empty()) {
            // O(log(n)) get smallest distance from priority queue
            auto nearest = pq.top().first;
            visit[nearest] = true;
            pq.pop();
            for (auto& adj:graph[nearest]) {
                // update the distance
                if (dist[adj.first] > dist[nearest] + adj.second) {
                    dist[adj.first] = dist[nearest] + adj.second;
                    // if distance is updated, it need to be revisit
                    visit[adj.first] = false;
                }
                if (!visit[adj.first]) {
                    // add reachable vertices to the heap
                    pq.push(std::make_pair(adj.first, dist[adj.first]));
                    visit[adj.first] = true;
                }
            }
        }
    }
/**
 * @brief print all distance from source vertex
 * 
 */
    void printDist() {
        std::cout << "print distances from source(max_dist means unreachable vertices): \n";
        for (int i = 0; i < dist.size(); ++i) {
            std::cout << i << "\t" << dist[i] << "\n";
        }
    }
/**
 * @brief only print distance to interested goal vertices
 * 
 * @tparam T 
 * @param order goal vertices array
 */
    template <class T>
    void printDist(T& order) {
        std::cout << "print distances from source(max_dist means unreachable vertices): \n";
        for (auto& i:order) {
            std::cout << dist[i] << ",";
        }
        std::cout << "\n";
    }
};
# endif /* DIJKSTRA_H_ */