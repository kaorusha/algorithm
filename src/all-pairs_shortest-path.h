# ifndef ALL_PAIRS_SHORTEST_PATH_H_
# define ALL_PAIRS_SHORTEST_PATH_H_
# include "util.h"
# include "dijkstra_shortest_path.h"
struct Edge {
    int tail;
    int head;
    int length;
    Edge():tail(0), head(0), length(0) {}
    Edge(int t, int h, int l):tail(t), head(h), length(l){}
};
/**
 * @brief Finds all pairs shortest path (APSP) of a graph in the form of distance matrix
 * example:
 * int main ()
{
    AllPairsShortestPath test;
    if (!ReadData("../data/_6ff856efca965e8774eb18584754fd65_g3.txt", true, test))
    // for large test data, use data/_919f8ed0c52d8b5926aa7e3fdecc2d32_large.txt
        std::cout << "fail reading data.\n";
    std::cout<< test.ShortestShortestPath() << "\n";
    return 0;
}
 */
class AllPairsShortestPath {
private:
    int vertex_num;
    int edge_num;
    std::vector<Edge> edges;
    int inf_dist;
public:
/**
 * @brief Construct a new All Pairs Shortest Path object
 * 
 * @param max_dist value to represent infinite distance, mind overflow after Reweighting()
 */
    AllPairsShortestPath (int max_dist):inf_dist(max_dist) {}
    AllPairsShortestPath ():inf_dist(INT16_MAX) {}
    void ProcessHeader (std::string& line) {
        std::istringstream ss(line);
        ss >> this->vertex_num >> this->edge_num;
    }
    void ProcessLine (std::string& line) {
        std::istringstream ss(line);
        int t, h, l;
        ss >> t >> h >> l;
        this->edges.emplace_back(t,h,l);
        if (l > this->inf_dist) std::cout<< "warning: exceed max dist\n";
    }
    /*
    void print(std::vector<Edge>& edges) {
        for (auto& edge:edges)
            std::cout << edge.tail << ", " << edge.head << ", " << edge.length << "\n";
    }*/
    /**
     * @brief find distances of single source shortest path (SSSP) with complexity O(n*m). 
     * @param edges list of graph edge 
     * @param n vertices number
     * @param source source vertex label
     * @param distances placeholder from source to other vertices
     * @param predecessor placeholder for reconstruction
     * @return true if no negative cycle found 
     */
    bool BellmanFord(std::vector<Edge>& edges, int& n, int& source, std::vector<int>& distances, std::vector<int>& predecessor) {
        distances.resize(n + 1, this->inf_dist);
        predecessor.resize(n + 1, -1);
        distances[source] = 0;
        for (int i = 1; i < n - 1; ++i) {
            for (Edge& edge:edges) {
                if (distances[edge.tail] + edge.length < distances[edge.head]) {
                    distances[edge.head] = distances[edge.tail] + edge.length;
                    predecessor[edge.head] = edge.tail;
                }
            }
        }
        // check if there is negative cycle
        for (Edge& edge:edges) {
            if (distances[edge.tail] + edge.length < distances[edge.head]) {
                std::cout << "error: has negative cycle\n";
                return false;
            }
        }
        return true;
    }
    /**
     * @brief change the negative edge length or weight as input of dijkstra
     * 
     * @param edges original graph
     * @param dist distance to artificial vertex, use this to make offset
     */
    void Reweighting(std::vector<Edge>& edges, std::vector<int> dist) {
        for (auto& edge:edges)
            edge.length = edge.length + dist[edge.tail] - dist[edge.head];
    }
    /**
     * @brief find all-pairs shortest path (APSP) in complexity O(mn log n)
     * 
     * @param edges Directed graph G = (V , E ), general edge lengths c e .
     * @param n number of vertices
     * @return std::vector<std::vector<int>>
     */
    std::vector<std::vector<int>> JohnsonAlgo (std::vector<Edge>& edges, int& n) {
        std::vector<std::vector<int>> dist_matrix;
        // (1) Form G' by adding a new vertex s and a new edge (s, v ) with
        //     length 0 for each v ∈ G .
        int s = 0;
        std::vector<Edge> new_graph = edges;
        for (int i = 1; i <= n; ++i) new_graph.emplace_back(s, i, 0);
        
        // (2) Run Bellman-Ford on G' with source vertex s. [If B-F detects a
        //     negative-cost cycle in G' (which must lie in G ), halt + report this.]
        std::vector<int> distances, predecessor;
        if (!BellmanFord(new_graph, n, s, distances, predecessor)) {
            std::cout << "the graph contains negative cycle.";
            return dist_matrix;
        }
        
        // (3) For each v ∈ G , define p v = length of a shortest s → v path in G'.
        //     For each edge e = (u, v ) ∈ G , define c'e  = c e + p u − p v .
        Reweighting(edges, distances);

        // (4) For each vertex u of G : Run Dijkstra’s algorithm in G , with edge
        //     lengths {c'e}, with source vertex u, to compute the shortest-path
        //     distance d'(u, v ) for each v ∈ G .
        DijkstraShortestPath adjacent_list(n, this->inf_dist);
        for (auto& edge:edges) adjacent_list.AddEdge(edge.tail, edge.head, edge.length);
        dist_matrix.resize(n + 1);
        dist_matrix[0] = std::vector<int>(n+1, this->inf_dist);
        for (int u = 1; u <= n; ++u) dist_matrix[u] = adjacent_list.shortestPath(u);

        // (5) For each pair u, v ∈ G , return the shortest-path distance
        //     d(u, v ) := d'(u, v ) − p u + p v
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                dist_matrix[u][v] = dist_matrix[u][v] - distances[u] + distances[v];
            }
        }
        
        return dist_matrix;
    }
    /**
     * @brief compute all-pairs shortest paths and remember the smallest one (i.e., compute min ⁡d(u,v), u,v∈V, 
     * where d(u,v) denotes the shortest-path distance from u to v). 
     * 
     * @return int dist
     */
    int ShortestShortestPath() {
        std::vector<std::vector<int>> d = JohnsonAlgo(this->edges, this->vertex_num); 
        int min = this->inf_dist;
        if (d.empty()) return min; // contains negative circle    
        for (int u = 1; u <= this->vertex_num; ++u) {
            for (int v = 1; v <= this->vertex_num; ++v) {
                if (u == v) continue;
                min = (min < d[u][v])?min:d[u][v];
            }
        }
        return min;
    }
};
# endif /* ALL_PAIRS_SHORTEST_PATH_H_ */