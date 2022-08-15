# ifndef CLUSTERING_H_
# define CLUSTERING_H_
# include "util.h"
# include <algorithm>
class Clustering {
private:
    int vertex_num;
    std::vector<int> leader;
    std::vector<int> rank;
    int cluster_num;
    typedef std::pair<int,int> Edge;
    typedef std::vector<std::pair<Edge,int>> Graph;
    Graph graph; 
public:
    Clustering () {}
    void ProcessHeader(std::string line) {
        this->vertex_num = std::stoi(line);
        this->cluster_num = this->vertex_num; 
    }
    /**
     * @brief This file describes a distance function (equivalently, a complete graph with edge costs).  It has the following format:

                [number_of_nodes]

                [edge 1 node 1] [edge 1 node 2] [edge 1 cost]

                [edge 2 node 1] [edge 2 node 2] [edge 2 cost]
     * 
     * @param line 
     */
    void ProcessLine(std::string line) {
        int node_1, node_2, cost;
        std::istringstream ss(line);
        ss >> node_1 >> node_2 >> cost;
        Edge edge{node_1, node_2};
        graph.emplace_back(std::make_pair(edge, cost));
    }
    /**
     * @brief Just like Kruskal’s MST algorithm, but stopped early. Called single-link clustering
     * 
     * @param desired_cluster_num 
     */
    int GreedyKruskalMST(int desired_cluster_num) {
        // at the beginning the leader points to vertex itself
        for (int i = 0; i <= this->cluster_num; ++i) this->leader.emplace_back(i);
        // at the beginning the rank for each vertex is 0
        this->rank.resize(this->vertex_num+1, 0);
        std::sort(graph.begin(), graph.end(), [](auto& a, auto& b){ return (a.second < b.second); });
        int i = 0;
        //printGraph(graph);
        while (this->cluster_num > desired_cluster_num) {
            Merge(graph[i].first);
            ++i;
        }
        // next distance
        --i;
        while ( Find(graph[i].first.first) == Find(graph[i].first.second)) ++i;
        return graph[i].second;
    }
    // find the root of this cluster
    int Find(int x) {
        int parent = this->leader[x];
        if (parent != x) {
            while (parent != this->leader[parent]) parent = this->leader[parent];
        }
        return parent;
    }
    // union two cluster into one
    void Union (int x, int y) {
        // change root
        if ( x != y) {
            // if two rank is the same, add 1 to one of them 
            if (this->rank[x] == this->rank[y]) ++this->rank[x];
            // make vertex with higher rank as new root
            if (this->rank[x] > this->rank[y]) this->leader[y] = x;
            else this->leader[x] = y;
            --this->cluster_num;
        }
    }
    void Merge(Edge& edge) {
        int node_1 = edge.first;
        int node_2 = edge.second;
        int root_1 = Find(node_1);
        int root_2 = Find(node_2);
        Union(root_1, root_2);
    }
    int GetEdgeSize() { return graph.size(); }
    
};
# endif /* CLUSTERING_H_ */