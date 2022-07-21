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

/**
 * @brief Read vector<int> data from a file
 * 
 * @param file_name Name of file containing control measurements.
 * @return True if opening and reading file was successful
 */
inline bool ReadVectorData (const std::string& file_name,
                                    std::vector<int>& v) {
    // Get file of integers
    std::ifstream is(file_name.c_str(), std::ifstream::in);
    // Return if we can't open the file
    if (!is) return false;

    // Declare single line of file:
    std::string line;
    
    // Run over each single line:
    while (std::getline(is, line)) {
        v.emplace_back(std::stoi(line));
    }
    return true;
}


# endif /* UTIL_H_ */