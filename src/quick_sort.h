# ifndef QUICK_SORT_H_
# define QUICK_SORT_H_
# include <vector>
# include <iostream>
# include "util.h"
# include <algorithm>
class QuickSort {
public:
    QuickSort () {}
    enum pivot_mode {
        first,      // first element of the divided range
        last,       // last element of the divided range
        random,     // random element of the divided range
        middle,     // middle element of the divided range (k-th element of 2*k size)
        median      /** choose the index with median value from three elements (
                    * the first, the last, and the middle element) of a vector 
                    * with distinct value **/
    };
    /**
     * @brief given chosen pivot position and return the index 
     * 
     * @param v input vector
     * @param l left index of chosen range
     * @param r right index of chosen range
     * @param mode determine the pivot, first as default
     * @return int index of pivot
     */
    int PickPivot(std::vector<int>& v, int l, int r, pivot_mode mode = first) {
        if (mode == first) return l;
        else if (mode == last) return r;
        else if (mode == random) std::cout << "random mode not implement yet";
        else if (mode == middle) return l + (r - l)/2;
        else if (mode == median) { 
            int middle = l + (r - l)/2;
            int idx[] = {l, middle, r};
            int value[] = {v[l],v[middle],v[r]};
            std::sort(value, value+3);
            for (auto& i: idx) {
                if (v[i] == value[1]) return i;
            }
        }
        else std::cout << "this mode not implement yet";
        return l;
    }
    /**
     * @brief use given pivot index for partition
     * 
     * @param v vector with distinct value
     * @param l left index of divided range of vector
     * @param r right index of divided range of vector
     * @param pivot index of pivot, will be updated after partition
     * @return int counted comparison times
     */
    int Partition (std::vector<int>& v, int l, int r, int& pivot) {
        // first swap pivot with first element
        std::swap(v[l], v[pivot]);
        int i = l+1;
        for (int j = l+1; j <= r; ++j) {
            if (v[j] < v[l]) std::swap(v[j], v[i++]);
        }
        std::swap(v[l], v[--i]);
        // update pivot position
        pivot = i;
        return r - l;
    }
    /**
     * @brief O(n*log(n)) quick sort with given pivot chosen mode
     * 
     * @param v vector with distinct value
     * @param l left index of range
     * @param r right index of range
     * @param mode determine pivot chosen position
     * @return int counted comparison times
     */
    int Sort (std::vector<int>& v, int l, int r, pivot_mode mode) {
        int count = 0;
        int p = PickPivot(v, l, r, mode);
        if (r > l) {
            count += Partition(v, l, r, p);
            count += Sort(v, l, p - 1, mode);
            count += Sort(v, p + 1, r, mode);
        }
        return count;
    }
};
# endif /* QUICK_SORT_H_ */