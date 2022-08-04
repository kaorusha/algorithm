# ifndef MEDIUM_MAINTENANCE_H_
# define MEDIUM_MAINTENANCE_H_
# include <queue>
/**
 * @brief Given a stream of unsorted numbers, arriving one by one. 
 * Letting xi denote the ith number of the file, the kth median m[k]
 * is defined as the median of the numbers x1,…,xk​. (So, if k is odd, 
 * then m[k]​ is ((k+1)/2)th smallest number among x1,…,xk​; if k is even, 
 * then m[k]​ is the (k/2)th smallest number among x1,…,xk​.)
 * 
 */
class MediumMaintenance {
private:
    std::priority_queue<int, std::vector<int>, std::less<int>> low_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> high_heap;
public:
/**
 * @brief Construct a new Medium Maintenance object
 * 
 */
    MediumMaintenance () {}
/**
 * @brief adding new sample and feedback the new medium
 * 
 * @param input received sample
 * @return int updated medium number
 */
    int update (int input) { 
        high_heap.push(input);
        // rebalancing the size of both heap
        while (high_heap.size() > low_heap.size()) {
            low_heap.push(high_heap.top());
            high_heap.pop();
        }
        if (high_heap.top() < low_heap.top()) {
            auto low = low_heap.top();
            low_heap.pop();
            auto high = high_heap.top();
            high_heap.pop();
            low_heap.push(high);
            high_heap.push(low);
        }
        return low_heap.top();
    }
};
# endif /* MEDIUM_MAINTENANCE_H_ */