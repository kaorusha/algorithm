# ifndef SPLIT_INV_H_
# define SPLIT_INV_H_
# include <vector>
# include <iostream>
# include <fstream>
class SplitInv {
private:
    template <class T>
    void print(T& v) {
        for (auto& i:v) std::cout<< i << ", ";
        std::cout << "\n";
    }
public:
    SplitInv () {}
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
    /**
     * @brief top down recursive to merge left and right sorted vector. 
     * Constraint: index is less than INT_MAX
     * @param l first index
     * @param r last index
     * @param v vector
     * @return long int counted inversions
     */
    long MergeSort (int l, int r, std::vector<int>& v) {
        long count = 0;
        if (l < r)  {
            auto m = l + (r - l)/2;
            count += MergeSort(l, m, v);
            count += MergeSort(m+1, r, v);
            count += CountSplitInv (l, r, v);
        }
        return count;
    }
    /**
     * @brief merge and sort two vectors, simultaneously count inversions
     * 
     * @param l first index
     * @param r last index
     * @param v vector
     * @return long int counted inversions  
     */
    long CountSplitInv (int l, int r, std::vector<int>& v) {
        // merged vector size
        int n = r - l + 1;
        int m = l + (r - l)/2 + 1; //the first index of the right half sorted vector
        std::vector<int> temp;
        temp.resize(n);
        int i = l;
        int j = m; 
        long ans = 0;
        // doing merge and count
        for (int k = 0; k < n; ++k) {
            if (i < m && j <= r) {
                if (v[i] < v[j]) {
                    temp[k] = v[i++];
                } else { // vector contains distinct value, i and j are distinctive
                    temp[k] = v[j++];
                    ans += (m - i);
                }
            } else if (i < m) temp[k] = v[i++];
            else temp[k] = v[j++];
        }
        std::swap_ranges(v.begin() + l, v.begin() + r + 1, temp.begin());
        return ans;
    }
    
};
# endif /* SPLIT_INV_H_ */