# ifndef COUNT_SPLIT_INV_H_
# define COUNT_SPLIT_INV_H_
# include <vector>
# include <iostream>
# include <fstream>
# include <algorithm>
class CountSplitInv {
private:
    template <class T>
    void print(T& v) {
        for (auto& i:v) std::cout<< i << ", ";
        std::cout << "\n";
    }
public:
    CountSplitInv () {}
    /**
     * @brief Read vector<int> data from a file
     * 
     * @param file_name Name of file containing control measurements.
     * @return True if opening and reading file was successful
     */
    inline bool read_vector_data (const std::string& file_name,
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
    int count_split_inv (std::vector<int>& v) {
        int n = v.size();
        std::sort(v.begin(), v.begin() + n / 2);
        std::sort(v.begin() + n / 2, v.end());
        int i = 0;
        int j = n/2;
        int ans = 0;
        // doing merge and count
        for (int k = 0; k < n; ++k) {
            if (v[i] < v[j]) {
                ++i;
            } else { // the elements are distinctive
                ans += (n/2 - i);
                ++j;
            }
        }
        return ans;
    }
    
};
# endif /* COUNT_SPLIT_INV_H_ */