# ifndef UTIL_H_
# define UTIL_H_
# include <vector>
# include <iostream>
# include <fstream>

template <class T>
void print(T& v) {
    for (auto& i:v) std::cout<< i << ", ";
    std::cout << "\n";
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


# endif /* UTIL_H_ */