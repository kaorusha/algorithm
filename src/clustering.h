# ifndef CLUSTERING_H_
# define CLUSTERING_H_
# include "util.h"
# include <algorithm>
/**
 * @brief use lazy union find for clustering, dominated by sorting complexity O(nlog(n))
 * example:
 * int main ()
{
    Clustering test;
    if(ReadData("../data/_fe8d0202cd20a808db6a4d5d06be62f4_clustering1.txt", true, test))
        std::cout << "read data with " << test.GetEdgeSize() << " elements\n";
    std::cout << test.GreedyKruskalMST(4) << "\n";
    return 0;
}
 */
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
    void InitBookkeeping (int v) {
        // at the beginning the leader points to vertex itself
        for (int i = 0; i <= v; ++i) this->leader.emplace_back(i);
        // at the beginning the rank for each vertex is 0
        this->rank.resize(v+1, 0);
    }
    void SetClusterNum(int n) {this->cluster_num = n;}
    int GetClusterNum() {return this->cluster_num;}
    void ProcessHeader(std::string line) {
        this->vertex_num = std::stoi(line);
        SetClusterNum(this->vertex_num);
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
        InitBookkeeping(this->vertex_num); 
        std::sort(graph.begin(), graph.end(), [](auto& a, auto& b){ return (a.second < b.second); });
        int i = 0;
        //printGraph(graph);
        while (this->cluster_num > desired_cluster_num) {
            Merge(graph[i].first.first, graph[i].first.second);
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
    void Merge(int x, int y) {
        int root_x = Find(x);
        int root_y = Find(y);
        Union(root_x, root_y);
    }
    int GetEdgeSize() { return graph.size(); }
    
};
# endif /* CLUSTERING_H_ */