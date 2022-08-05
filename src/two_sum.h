# ifndef TWO_SUM_H_
# define TWO_SUM_H_
# include <vector>
# include <iostream>
# include <algorithm>
/**
 * @brief given target value t such that there are distinct numbers x,y in the array that satisfy x+y=t
 *  
 */
class TwoSum {
private:
    template <class T>
    void printHash(T& v, int shift) {
        for (int i = 0; i < v.size(); ++i) {
            if (v[i]) std::cout << i + shift << ",";
        }
        std::cout << "\n";
    }
public:
    TwoSum(){}
    /**
     * @brief t in the range of [target_lower, target_upper], that there are distinct numbers x,y in the input array that satisfy x+y=t
     * 
     * @param target_lower 
     * @param target_upper 
     * @param input sorted array
     * @return int number of the targets
     */
    template<class T>
    int NumWithinRange(const int target_lower, const int target_upper, T& input) {
        int n = target_upper - target_lower + 1;
        std::sort(input.begin(), input.end());
        std::vector<bool> hashmap(n, false);
        int l = 0;
        int r = input.size()-1;
        
        while (l < r) {
            long sum = input[l] + input[r];
            if ( sum < (long)target_lower) ++l;
            else if (sum > (long) target_upper) --r;
            else {
                for (int i = r; i > l; --i) {
                    if (input[l] == input[i]) { 
                        //std::cout << "x, y is both " << input[l] << "\n";
                        continue;
                    }
                    long key = input[l] + input[i] - target_lower;
                    //std::cout << "l = " << l  << "\tr = " << i << "\tkey = " << key << "\n";
                    if (key < n && key >= 0) hashmap[key] = true;
                }
                // ignore numbers that already seen
                while (input[l] == input[l+1]) ++l;
                ++l;
            }
            if (input[l] > target_upper/2) break;
        }
        int count = 0;
        for (auto n:hashmap) {
            if (n) ++count;
        }
        //printHash(hashmap, target_lower);
        return count;
    }
};
# endif /* TWO_SUM_H_ */