# ifndef KOSARAJU_H_
# define KOSARAJU_H_
# include <sstream>
# include <fstream>
# include <iostream>
# include <vector>
# include <unordered_map>

typedef std::unordered_map<int, std::vector<int>> Graph;
/**
 * @brief Kosaraju algorithm (the key: scc is the same for reversed graph)
 * example:
int main ()
{
    Graph graph;
    Graph graph_rev;
    Kosaraju test(875714);
    const std::string file = "../data/_410e934e6553ac56409b2cb7096a44aa_SCC.txt"; // node num = 875714
    if (!test.ReadGraphData(file, graph)) std::cout << "fail reading data!\n";
    if (!test.ReadGraphData(file, graph_rev, true)) std::cout << "fail reading data!\n";        
    test.findSCC(graph, graph_rev);
    return 0;
} 
 */
class Kosaraju {
private:
    std::vector<bool> visit;
    std::vector<int> f;
    std::vector<int> depth_order;
    std::vector<int> leader;
    int t;
    int s;
    int max_vertex_num;
public:
/**
 * @brief Construct a new Kosaraju object
 * 
 * @param n the number of vertices on the graph
 */
    Kosaraju (int n):t(0), s(0), max_vertex_num(n) {}
/**
 * @brief Set the Vertex Num object to prepare the bookkeeping vectors
 * 
 * @param n 
 */
    void setVertexNum(int n) {
        this->leader.resize(n + 1);
        this->f.resize(n + 1);
        this->visit.resize(n + 1);
        this->depth_order.resize(n+1);
    }
/**
 * @brief read and store graph data
 * 
 * @param file_name 
 * @param graph address to store the data
 * @param reverse weather to reverse the direction of the graph
 * @return true if the file is open and parsed
 * @return false if fail opening the file
 */
    inline bool ReadGraphData (const std::string& file_name, Graph& graph, bool reverse = false) {
        // Get file of integers
        std::ifstream is(file_name.c_str(), std::ifstream::in);
        // Return if we can't open the file
        if (!is) return false;

        // Declare single line of file:
        std::string line;
        
        // Run over each single line:
        while (std::getline(is, line)) {
            std::istringstream linestream(line);
            int from, to;
            linestream >> from >> to;
            if (reverse) std::swap(from, to);
            // check vertex label within limit
            if (from > max_vertex_num) {
                std::cout << "update max vertex num to " << from << " \n";
                this->max_vertex_num = from;
            }
            if (to > max_vertex_num) {
                std::cout << "update max vertex num to " << to << " \n";
                this->max_vertex_num = to;
            }
            graph[from].emplace_back(to);
        }
        is.close();
        std::cout << "done reading graph data with " << graph.size() << " vertices.\n";
        return true;
    }
    void reverseDFS (Graph& g, int i) {
        visit[i] = true;
        for (auto& next_vertex:g[i]) {
            if (!visit[next_vertex]) reverseDFS(g, next_vertex);
        }
        ++this->t;
        this->f[i] = this->t;
        this->depth_order[this->t] = i;
    }
/**
 * @brief Set the Finishing Time object to find the order of depth of sink vertices
 * 
 * @param g reversed graph
 */
    void SetFinishingTime(Graph& g) {
        for (int i = this->max_vertex_num; i > 0; --i) {
            if (!visit[i]) {
                reverseDFS(g, i);
            }
        }
    }
    void DFS (Graph& g, int i) {
        visit[i] = false;
        this->leader[i] = this->s;
        for (auto& next_vertex:g[i]) {
            if (visit[next_vertex]) DFS(g, next_vertex);
        }
    }
/**
 * @brief Set the Leader object, grouping ssc with leader sink vertex
 * 
 * @param g original graph
 */
    void SetLeader(Graph& g) {
        for (int i = this->max_vertex_num; i > 0; --i) {
            int deepest_vertex = this->depth_order[i];
            if (visit[deepest_vertex]) {
                this->s = deepest_vertex;
                DFS(g, deepest_vertex);
            }
        }
    }
    void print(Graph& g) {
        for (auto& i:g) {
            std::cout << i.first << "\t";
            print(i.second);
        }
    }
    template <class T>
    void print(T& v) {
        for (auto i:v) std::cout << i << ", ";
        std::cout << "\n";
    }
/**
 * @brief given graph and reverse graph, find the top 5 strongly connected components (SCC)
 * 
 * @param g graph data
 * @param g_rev reversed graph data
 */
    void findSCC (Graph& g, Graph& g_rev) {
        setVertexNum(this->max_vertex_num);
        SetFinishingTime(g_rev);
        std::cout << "set finishing time done.\n";
        SetLeader(g);
        //print(this->f);
        //print(this->leader);
        // make a list to count leader and memorize top 5 leader label
        std::vector<int> count(this->max_vertex_num + 1, 0);
        for (int i = 1; i <= this->max_vertex_num; ++i) ++count[leader[i]];
        std::vector<int> top(5,-1);
        for (auto& i:count) {
            if (i > top[0]) {
                top[4] = top[3];
                top[3] = top[2];
                top[2] = top[1];
                top[1] = top[0];
                top[0] = i;
            } else if (i > top[1]) {
                top[4] = top[3];
                top[3] = top[2];
                top[2] = top[1];
                top[1] = i;
            } else if (i > top[2]) {
                top[4] = top[3];
                top[3] = top[2];
                top[2] = i;
            } else if (i > top[3]) {
                top[4] = top[3];
                top[3] = i;
            } else if (i > top[4]) {
                top[4] = i;
            }
        }        
        print(top);
    }
};
# endif /* SCC_H_ */