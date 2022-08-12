# ifndef UTIL_H_
# define UTIL_H_
# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
template <class T>
void print(std::pair<T, T>& pair) {
    std::cout << pair.first << ", " << pair.second << "\t";
}
template <class T>
void print(std::vector<T>& v) {
    for (auto& i:v) std::cout << i << ", ";
    std::cout << "\n";
}
template <class T>
void printGraph(std::vector<T>& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        std::cout << i << "\t";
        for (auto& i:graph[i]) print(i);
        std::cout << "\n";
    }
}

long stoT(std::string& s) {
    return std::stol(s);
}

/**
 * @brief Read vector<int> data from a file
 * 
 * @param file_name Name of file containing control measurements.
 * @return True if opening and reading file was successful
 */
template <class T>
inline bool ReadVectorData (const std::string& file_name, T& v) {
    // Get file of integers
    std::ifstream is(file_name.c_str(), std::ifstream::in);
    // Return if we can't open the file
    if (!is) return false;

    // Declare single line of file:
    std::string line;
    
    // Run over each single line:
    while (std::getline(is, line)) {
        v.emplace_back(stoT(line));
    }
    return true;
}
/**
 * @brief the next vertex this edge point to and its weight or cost for choosing this path
 * [vertex, wright]
 */
typedef std::pair<int, int> Edge;
typedef std::vector<std::vector<Edge>> Graph;
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
template <class T>
inline bool ReadEdgeData (const std::string& file_name, T& graph, int& vertex_num, int& edge_num) {
    // Get file of integers
    std::ifstream is(file_name.c_str(), std::ifstream::in);
    // Return if we can't open the file
    if (!is) return false;

    // Declare single line of file:
    std::string line;

    // read first line
    std::getline(is, line);
    std::istringstream ss(line);
    ss >> vertex_num >> edge_num;
    graph.resize(m + 1);
    // Run over each single line:
    while (std::getline(is, line)) {
        int one, another, weight;
        std::istringstream ss(line);
        ss >> one >> another >> weight;
        if (one > vertex_num || another > vertex_num)
            std::cout << "warning: vertex babel exceed vertex number\n";
        // since the graph is undirected
        graph[one].emplace_back(Edge{another, weight});
        graph[another].emplace_back(Edge{one, weight});
    }
    return true;
}

# endif /* UTIL_H_ */