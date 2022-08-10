# ifndef PRIMS_MINIMUM_SPANNING_TREE_H_
# define PRIMS_MINIMUM_SPANNING_TREE_H_
# include "util.h"
/**
 * @brief the next vertex this edge point to and its weight or cost for choosing this path
 * [vertex, wright]
 */
typedef std::pair<int, int> Edge;
typedef std::vector<std::vector<Edge>> Graph;
/**
 * @brief Prim's minimum spanning tree algorithm
 * example: 
int main ()
{
    PrimsMinimumSpanningTree test(INT32_MAX);
    Graph g;
    if(test.ReadGraph("../data/_d4f3531eac1d289525141e95a2fea52f_edges.txt", g));
        std::cout << "read data with " << g.size() << " elements\n";
    //printGraph(g);
    test.findMST(g, 1);
    std::cout << test.cost() << "\n";

    return 0;
}
 */
class PrimsMinimumSpanningTree {
private:
    int vertex_num;
    int edge_num;
    std::vector<int> mst;
    std::vector<bool> visit;
    std::vector<int> key;
    int max_w;
public:
    /**
     * @brief Construct a new Prims Minimum Spanning Tree object
     * 
     */
    PrimsMinimumSpanningTree(int max_weight):max_w(max_weight) {}
    /**
     * @brief read graph data from file
     * 
     * @param file_name This file describes an undirected graph with integer edge costs.  It has the format

[number_of_nodes] [number_of_edges]

[one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]

[one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]
     * @param graph storage address 
     * @return true 
     * @return false 
     */
    inline bool ReadGraph (const std::string& file_name, Graph& graph) {
        // Get file of integers
        std::ifstream is(file_name.c_str(), std::ifstream::in);
        // Return if we can't open the file
        if (!is) return false;

        // Declare single line of file:
        std::string line;

        // read first line
        std::getline(is, line);
        std::istringstream ss(line);
        ss >> this->vertex_num >> this->edge_num;
        graph.resize(this->vertex_num + 1);
        // Run over each single line:
        while (std::getline(is, line)) {
            int one, another, weight;
            std::istringstream ss(line);
            ss >> one >> another >> weight;
            if (one > this->vertex_num || another > this->vertex_num)
                std::cout << "warning: vertex babel exceed vertex number\n";
            // since the graph is undirected
            graph[one].emplace_back(Edge{another, weight});
            graph[another].emplace_back(Edge{one, weight});
        }
        return true;
    }
    /**
     * @brief given an graph and starting vertex, find the minimum spanning tree from 
     * starting vertex. 
     * complexity:  O(m*n) with m = number of edge, n = number of vertices
     * @param graph 
     * @param start_vertex 
     */
    void findMST(Graph& graph, int start_vertex) {
        this->key.resize(this->vertex_num + 1, this->max_w);
        this->visit.resize(this->vertex_num + 1, false);
        mst.emplace_back(start_vertex);
        visit[start_vertex] = true;
        key[start_vertex] = 0;
        while (mst.size() != this->vertex_num) {
            int min_weight = this->max_w;
            int next_vertex = -1;
            // can implement heap supporting key deletion to get O(log(n)) complexity
            for (auto& vertex:mst) {
                for (auto& edge:graph[vertex]) {    
                    if (!visit[edge.first]) {
                        // for vertex not being chosen in mst, the key might be less
                        if (edge.second < key[edge.first]) 
                            key[edge.first] = edge.second;
                        // find minimum weight among reachable vertices
                        if (edge.second < min_weight) {
                            min_weight = edge.second;
                            next_vertex = edge.first;
                        }
                    }
                }
            }
            mst.emplace_back(next_vertex);
            visit[next_vertex] = true;
        }
    }
    /**
     * @brief report the overall cost of a minimum spanning tree
     * 
     * @return int 
     */
    int cost() {
        int sum = 0;
        for (auto& vertex:this->mst)
            sum += key[vertex];
        return sum;
    }
};
# endif /* PRIMS_MINIMUM_SPANNING_TREE_H_ */