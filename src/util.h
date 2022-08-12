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
 * @brief 
 * 
 * @tparam Obj
 * @param file_name 
 * @param has_header_line if the first line has to process separately
 * @param o object contains the method for processing each line of the file, and also storage space
 * @return true 
 * @return false 
 */
template <class Obj>
inline bool ReadData (const std::string& file_name, bool has_header_line, Obj& o) {
    // Get file of integers
    std::ifstream is(file_name.c_str(), std::ifstream::in);
    // Return if we can't open the file
    if (!is) return false;

    // Declare single line of file:
    std::string line;

    // read first line
    if (has_header_line) {
        std::getline(is, line);
        o.ProcessHeader(line);
    }
    // Run over each single line:
    while (std::getline(is, line)) o.ProcessLine(line);
    return true;
}

# endif /* UTIL_H_ */