# ifndef CLUSTERING_BUG_H_
# define CLUSTERING_BUG_H_
# include "clustering.h"
# include <unordered_map>
# include <unordered_set>
/**
 * @brief The distance between two nodes u and v in this problem is defined as the Hamming distance--- 
 * the number of differing bits --- between the two nodes' labels.  For example, the Hamming distance 
 * between the 24-bit label of node #2 above and the label "0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1"
 * is 3 (since they differ in the 3rd, 7th, and 21st bits).
 * example:
 * int main ()
{
    ClusteringBig test;
    if(!ReadData("../data/_fe8d0202cd20a808db6a4d5d06be62f4_clustering_big.txt", true, test))
        std::cout << "fail opening file";
    std::cout << "cluster num: " << test.MergeDistance() << "\n";
    return 0;
}
 */
class ClusteringBig {
private:
    typedef std::vector<bool> Key; // store the hamming distance in the form of the bit array
    Clustering base;
    int length; // bit numbers of Hamming distance
    std::unordered_map<Key, int> hamming_distance; //the hamming distance as key and its vertex index 
    int index;
public:
    ClusteringBig ():index(1) {}
    void ProcessHeader(std::string line) {
        std::string vertex_num;
        int bit_num;
        std::istringstream ss(line);
        ss >> vertex_num >> bit_num;
        // base class only take vertex number for header line
        base.ProcessHeader(vertex_num);
        if (bit_num > 31) std::cout << "fail: bit number exceed integer length.\n";
        this->length = bit_num;
    }
    /**
     * @brief  The format is:

                    [# of nodes] [# of bits for each node's label]

                    [first bit of node 1] ... [last bit of node 1]

                    [first bit of node 2] ... [last bit of node 2]

     * For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1" 
     denotes the 24 bits associated with node #2.
     * @param line 
     */
    void ProcessLine(std::string line) {
        Key key;
        bool bit;
        std::istringstream ss(line);
        while(ss >> bit) key.emplace_back(bit);
        // this step filter out the vertices with 0 distance;
        if (!hamming_distance.count(key)) {
            hamming_distance[key] = index;
            ++index;
        }
    }
    /**
     * @brief generate candidates with 1 hamming distance to the input source
     * complexity O(1) for constant bit length
     * @param source 
     * @param candidates 
     */
    void Distance1(Key source, std::unordered_set<Key>& candidates) {
        for (int i = 0; i < this->length; ++i) {
            Key candidate = source;
            candidate[i] = !candidate[i];
            candidates.emplace(candidate);
        }
    }
    /**
     * @brief generate candidates with 2 hamming distance to the input source
     * complexity O(1) for constant bit length
     * @param source 
     * @param candidates 
     */
    void Distance2(Key source, std::unordered_set<Key>& candidates) {
        for (int i = 0; i < this->length; ++i) {
            for (int j = i+1; j < this->length; ++j) {
                Key candidate = source;
                candidate[i] = !candidate[i];
                candidate[j] = !candidate[j];
                candidates.emplace(candidate);
            }
        }
    }
    void print(std::unordered_set<Key>& v) { for (auto i:v) print(i); }
    void print(Key& k) {
        for (auto b:k) std::cout << b << ",";
        std::cout << "\n";
    }
    /**
     * @brief the largest value of k such that there is a k-clustering with spacing at least 3. 
     * This method does not sorting distance, but to merge vertices with candidate keys
     * @return int clusters are needed to ensure that no pair of nodes with all but 2 bits in common get split into different clusters
     */
    int MergeDistance() {
        // prepare union find bookkeeping array
        int n = hamming_distance.size();
        base.InitBookkeeping(n);
        base.SetClusterNum(n);
        // O(N) scan all data
        for (auto it = hamming_distance.begin(); it != hamming_distance.end(); ++it) {
            std::unordered_set<Key> to_merge;
            //std::cout << "to_merge = \n";
            Distance1(it->first, to_merge);
            Distance2(it->first, to_merge);
            //print(to_merge);
            // O(1) for finding key and O(log(N) merge union find structure)
            for (auto key:to_merge) {
                auto i = hamming_distance.find(key);
                if (hamming_distance.count(key)) {
                    auto idx = hamming_distance[key];
                    base.Merge(it->second, idx);
                }
            }
        }
        return base.GetClusterNum();
    }
};
# endif /* CLUSTERING_BUG_H_ */