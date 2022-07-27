# ifndef KARGER_MIN_CUT_H_
# define KARGER_MIN_CUT_H_
# include <sstream>
# include <fstream>
# include <random>
# include <iostream>
# include <time.h>
# define MAX_VERTEX_NUM 200
typedef std::vector<std::pair<int,int>> Graph;
/**
 * @brief read the graph data, and store the number of vertex, count the minimum cut of that graph
 * 
 */
class KargerMinCut {
private:
    int vertex_num;
public:
    KargerMinCut (): vertex_num{0} {};
    /**
     * @brief read the file that contains the adjacency list representation of a simple undirected graph.
     * also check the vertex number. 
     * @param file_name graph data, for each row[i], the first column row[i][0] represent one vertex label, 
     * and the rest column row[i][j] is other vertices connected with row[i][0].   
     * @param graph represented by a set of edge (which is composed with two vertices) 
     * @return true if the file is open correctly,
     * @return false if not
     */
    inline bool ReadGraphData (const std::string& file_name, Graph& graph) {
        // Get file of integers
        std::ifstream is(file_name.c_str(), std::ifstream::in);
        // Return if we can't open the file
        if (!is) return false;

        // Declare single line of file:
        std::string line;
        
        // Use a matrix to avoid duplicate edge
        std::vector<std::vector<bool>> record(MAX_VERTEX_NUM, std::vector<bool>(MAX_VERTEX_NUM, false));
        
        // Run over each single line:
        while (std::getline(is, line)) {
            ++this->vertex_num;
            std::istringstream linestream(line);
            int vertex1, vertex2;
            linestream >> vertex1;
            while (linestream >> vertex2) {
                // for undirected graph, use smaller number for first label 
                std::pair<int, int> edge;
                if (vertex1 < vertex2) edge = std::make_pair(vertex1, vertex2);
                else edge = std::make_pair(vertex2, vertex1);
                if (record[edge.first-1][edge.second-1] == false) {
                    graph.emplace_back(edge);
                    record[edge.first-1][edge.second-1] = true;
                }
            }
        }
        // check the total number of vertex
        if (this->vertex_num > MAX_VERTEX_NUM) {
            std::cout << "vertex number " << this->vertex_num << " exceed constraints maximum " << MAX_VERTEX_NUM << "\n";
            return false;
        }
        is.close();
        return true;
    }
    void printGraph (Graph& graph) {
        for (auto& i:graph) std::cout << i.first << ", " << i.second << "\t";
        std::cout << "\n";
    }
    /**
     * @brief removes an edge from a graph while simultaneously merging the two vertices that it previously joined
     * 
     * @param graph graph data
     * @param remain the vertex label that we want to keep after removing the edge 
     * @param vanish the vertex label that we want to delete after removing the edge
     */
    void EdgeContraction (Graph& graph, int remain, int vanish) {
        //std::cout << "run (" << remain << ", " << vanish << "): \n";
        for (auto it = graph.begin(); it != graph.end(); ++it) {
            if (it->first == vanish) {
                //std::cout << "replace (" << it->first << ", " << it->second << ") with (" << remain << ", " << it->second << ")\t";
                it->first = remain;
            }
            else if (it->second == vanish) {
                //std::cout << "replace (" << it->first << ", " << it->second << ") with (" << it->first << ", " << remain << ")\t";
                it->second = remain;
            }
            // remove cyclic edge
            if (it->first == it->second) {
                graph.erase(it);
                --it;
            } else {
                if (it->first > it->second) {
                    auto temp = it->first;
                    it->first = it->second;
                    it->second = temp;
                }
            }
        }
        --this->vertex_num;
    }
    /**
     * @brief randomly contract edge to count minimum cut, run multiple times for true minimum.
     * note the graph is modified after return.
     * @param graph 
     * @return int counted cut
     */
    int CountMinCut(Graph& graph) {
        // Use a different seed value for every run.
        srand (time(NULL));
        while (this->vertex_num > 2) {
            // random pick one vertex
            int n = rand() % (graph.size());
            // remove cyclic edge
            if (graph[n].first == graph[n].second) {
                //graph.erase(graph.begin() + n);
                continue;
            } else {
                int remain = (graph[n].first < graph[n].second)? graph[n].first:graph[n].second;
                int vanish = (graph[n].first > graph[n].second)? graph[n].first:graph[n].second;
                EdgeContraction(graph, remain, vanish);
            }
        }
        return graph.size();
    }
};
# endif /* KARGER_MIN_CUT_H_ */