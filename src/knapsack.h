# ifndef KNAPSACK_H_
# define KNAPSACK_H_
# include "util.h"
/**
 * @brief dynamic programming solving knapsack problem
 * example:
 * int main ()
{
    Knapsack test;
    if(!ReadData("../data/_6dfda29c18c77fd14511ba8964c2e265_knapsack_big.txt", true, test))
        std::cout << "fail opening file";
    std::cout << test.MaxValue() << "\n";
    return 0;
}
 */
class Knapsack {
private:
    int capacity; // knapsack capacity
    int num; // input item number
    std::vector<int> value;
    std::vector<int> weight;
    
public:
    Knapsack(){ 
        // there no index 0, fill the corresponding index 0
        this->value.emplace_back(0);
        this->weight.emplace_back(0);
    }
    void ProcessHeader (std::string& line) {
        std::istringstream ss(line);
        ss >> this->capacity >> this->num;
    }
    void ProcessLine (std::string& line) {
        std::istringstream ss(line);
        int val, w;
        ss >> val >> w;
        this->value.emplace_back(val);
        this->weight.emplace_back(w);
    }
    bool CheckData () {
        if (this->value.size() != this->num + 1) return false;
        if (this->weight.size() != this->num + 1) return false;
        return true;
    }
    /**
     * @brief return only max value, without reconstruction of the set
     * 
     * @return int 
     */
    int MaxValue() {
        if (!CheckData()) {
            std::cout << "error: data number not match!\n";
            return -1;
        }
        // without reconstruction, only last iteration is memorized;
        std::vector<int> dp(this->capacity + 1, 0);
        for (int i = 1; i <= this->num; ++i) {
            std::vector<int> dp_next(this->capacity + 1, 0);
            for (int x = 0; x <= this->capacity; ++x) {
                int update;
                if (x < this->weight[i]) update = 0;
                else update = dp[x - this->weight[i]] + this->value[i];
                dp_next[x] = (dp[x] > update)? dp[x]:update;
            }
            dp = dp_next;
            //print(dp);
        }
        return dp[this->capacity];
    }
};
# endif /* KNAPSACK_H_ */