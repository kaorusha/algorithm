# ifndef GREEDY_SCHEDULING_H_
# define GREEDY_SCHEDULING_H_
# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>
/**
 * @brief the greedy algorithms for minimizing the weighted sum of completion times.
 * example:
 * int main ()
{
    std::vector<std::pair<int,int>> v;
    GreedyScheduling test;
    if(test.ReadWeightLength("../data/_642c2ce8f3abe387bdff636d708cdb26_jobs.txt", v))
        std::cout << "read data with " << v.size() << " elements\n";
    test.SortByDifference(v);
    std::cout << "sort by difference completion time = "<< test.CompletionTime(v) << std::endl;
    test.SortByRatio(v);
    std::cout << "sort by ratio completion time = "<< test.CompletionTime(v) << std::endl;
    return 0;
}
 */
class GreedyScheduling {
private:
    int num_job;
public:
    GreedyScheduling (){}
    /**
     * @brief 
     * 
     * @param file_name 
This file describes a set of jobs with positive and integral weights and lengths.  It has the format

[number_of_jobs]

[job_1_weight] [job_1_length]

[job_2_weight] [job_2_length] 
     * @param v storage space
     * @return true 
     * @return false 
     */
    inline bool ReadWeightLength(const std::string& file_name, std::vector<std::pair<int,int>>& v) {
        // Get file of integers
        std::ifstream is(file_name.c_str(), std::ifstream::in);
        // Return if we can't open the file
        if (!is) return false;

        // Declare single line of file:
        std::string line;

        // read first line
        std::getline(is, line);
        this->num_job = std::stoi(line);
        
        // Run over each single line:
        while (std::getline(is, line)) {
            int weight, length;
            std::istringstream ss(line);
            ss >> weight >> length;
            if (weight == 0 || length == 0) std::cout << "warning: zero weight or length!\n";
            v.emplace_back(std::make_pair(weight, length));
        }
        return true;
    }
    void SortByDifference(std::vector<std::pair<int, int>>& v) {
        std::sort(v.begin(), v.end(), [](const auto& a, const auto& b){ 
            // handling tie: compare weight
            if (a.first  - a.second == b.first - b.second)
                return (a.first > b.first);
            else return (a.first  - a.second > b.first - b.second);
        });
    }
    void SortByRatio(std::vector<std::pair<int, int>>& v) {
        std::sort(v.begin(), v.end(), [](const auto& a, const auto& b){
            return ((float)a.first/a.second >= (float)b.first/b.second);
        });
    } 
    /**
     * @brief return the sum of weighted completion times of the resulting schedule
     * 
     * @param v sorted schedule
     * @return int positive integer
     */
    long CompletionTime(std::vector<std::pair<int, int>>& v) {
        long sum = 0;
        long ans = 0;
        for (auto& i:v) {
            sum += i.second;
            ans += i.first * sum;
        }
        return ans;
    }
    void printJobs(std::vector<std::pair<int,int>>& v) {
        for (auto& i:v) {
            std::cout << i.first << ", " << i.second << "\tdiff = " << i.first - i.second <<"\n";
        }
    }

};
# endif /* GREEDY_SCHEDULING_H_ */