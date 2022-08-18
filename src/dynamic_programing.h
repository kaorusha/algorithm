# ifndef DYNAMIC_PROGRAMING_H_
# define DYNAMIC_PROGRAMING_H_
# include "util.h"
/**
 * @brief given an array of weight, pick maximum weight independent sets 
 * example
 * int main ()
{
    DynamicPrograming test;
    if(!ReadData("../data/_790eb8b186eefb5b63d0bf38b5096873_mwis.txt", true, test))
        std::cout << "fail opening file";
    std::vector<int> v = {1, 2, 3, 4, 17, 117, 517, 97};
    test.PrintIndex(v);
    return 0;
}
 * 
 */
class DynamicPrograming
{
private:
    /* data */
    int vertex_num;
    std::vector<int> weights;
    int idx;
public:
    DynamicPrograming(): idx(1) {};
    ~DynamicPrograming(){};
    void ProcessHeader (std::string& line) {
        this->vertex_num = std::stoi(line);
        weights.resize(this->vertex_num + 1);
    }
    /**
     * @brief This file describes the weights of the vertices in a path graph (with the weights listed in the order in which vertices appear in the path). It has the following format:

[number_of_vertices]

[weight of first vertex]

[weight of second vertex]

...

For example, the third line of the file is "6395702," indicating that the weight of the second vertex of the graph is 6395702. 
     * 
     * @param line 
     */
    void ProcessLine (std::string& line) {
        this->weights[idx] = std::stoi(line);
        ++idx;
    }
    /**
     * @brief find the maximum weight independent set, the returned index denotes the vertex index
     * (begin with 1)
     * @return std::vector<bool> 
     */
    std::vector<bool> MaximumWeightIndependentSet() {
        // scan and check maximum sofar
        std::vector<int> dp(this->vertex_num + 1, 0);
        dp[0] = 0;
        dp[1] = this->weights[1];
        for (int i = 2; i <= this->vertex_num; ++i) {
            if (this->weights[i] + dp[i-2] > dp[i-1]) dp[i] =  this->weights[i] + dp[i-2];
            else dp[i] = dp[i-1];
        }
        // print(dp);
        // reconstruction
        std::vector<bool> set(this->vertex_num + 1, false);
        int i = this->vertex_num;
        while (i > 0) {
            if (dp[i] > dp[i-1]) {
                set[i] = true;
                i -= 2;
            } else {
                set[i-1] = true;
                i -= 3;
            }
        }
        return set;
    }
    /**
     * @brief check wether the given index is included in the set
     * 
     * @param vertices index numbers to be checked
     */
    void PrintIndex(std::vector<int>& vertices){
        auto res = MaximumWeightIndependentSet();
        for (auto i:vertices) {
            std::cout << res[i];
        }
        std::cout<< "\n";
    }
};
# endif /* DYNAMIC_PROGRAMING_H_ */