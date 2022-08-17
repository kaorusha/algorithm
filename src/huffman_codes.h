# ifndef HUFFMAN_CODES_H_
# define HUFFMAN_CODES_H_
# include "util.h"
# include <queue>
# include <algorithm>
struct TreeNode {
    int weight;
    int symbol;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : weight(0), symbol(0), left(nullptr), right(nullptr) {}
    TreeNode(int w, int i) : weight(w), symbol(i), left(nullptr), right(nullptr) {}
    TreeNode(int w, int i, TreeNode *left, TreeNode *right) : weight(w), symbol(i), left(left), right(right) {}
};
/**
 * @brief Huffman code algorithm
 * example
 * int main ()
{
    HuffmanCodes test;
    if(!ReadData("../data/_eed1bd08e2fa58bbe94b24c06a20dcdb_huffman.txt", true, test))
        std::cout << "fail opening file";
    test.Run();
    return 0;
}
 * 
 */
class HuffmanCodes {
private:
    int vertex_num;
    std::vector<TreeNode*> symbols;
    int idx; // for denoting the symbol from data
public:
    HuffmanCodes ():idx(1) {}
    void ProcessHeader(std::string& line) {
        this->vertex_num = std::stoi(line);
    }
    /**
     * @brief 

        This file describes an instance of the problem. It has the following format:

        [number_of_symbols]

        [weight of symbol #1]

        [weight of symbol #2]

        ...

        For example, the third line of the file is "6852892," indicating that the weight of the second symbol of the alphabet is 6852892. 
     * 
     * @param line 
     */
    void ProcessLine(std::string& line) {
        int weight = std::stoi(line);
        this->symbols.emplace_back(new TreeNode(weight, idx));
        ++idx;
    }
    void PrintNodes(std::vector<TreeNode*>& v) {
        for (auto& i:v) {
            std::cout << i->symbol << ": " << i->weight << "\n";
        }
    }
    /**
     * @brief extract top element from queue
     * 
     * @param q 
     * @return TreeNode* 
     */
    TreeNode* Pop(std::queue<TreeNode*>& q) {
        auto node = q.front();
        q.pop();
        return node;
    }
    /**
     * @brief Get the Min object from two queue
     * 
     * @param l 
     * @param r 
     * @return TreeNode* 
     */
    TreeNode* GetMin(std::queue<TreeNode*>& l, std::queue<TreeNode*>& r) {
        if (r.empty()) return Pop(l);
        if (l.empty()) return Pop(r);
        if (l.front()->weight < r.front()->weight) return Pop(l);
        else return Pop(r);
    }
    TreeNode* BuildHuffmanTree(std::vector<TreeNode*>& sorted) {
        std::queue<TreeNode*> l,r;
        // begin with all sorted nodes in left queue, and empty right queue
        for (auto& node:sorted) l.emplace(node);
        // build tree
        int n = this->vertex_num;
        while (n > 1) {
            auto left = GetMin(l, r);
            auto right = GetMin(l, r);
            TreeNode* top = new TreeNode(left->weight + right->weight, 0, left, right);
            r.emplace(top);
            --n;
        }
        return r.front();
    }
    typedef std::string Code;
    void DFS(TreeNode* root, Code code, std::vector<Code>& list) {
        if (!root) return;
        if (!root->left && !root->right) {
            list[root->symbol] = code;
            return;
        }
        if (root->left) DFS(root->left, code + '0', list);
        if (root->right) DFS(root->right, code + '1', list);
    }
    /**
     * @brief print the symbol and corresponding code from a huffman tree, 
     * also count the maximum and minimum length of code
     * 
     * @param root 
     */
    void PrintCodes(TreeNode* root) {
        Code code;
        std::vector<Code> list;
        list.resize(this->vertex_num + 1);
        DFS(root, code, list);
        int min_len = this->vertex_num;
        int max_len = 0;
        // symbol 0 represent non leaf node so it is invalid
        for (int i = 1; i < list.size(); ++i) {
            std::cout << "symbol " << i << ":\t" <<  list[i] << "\n";
            int n = list[i].length();
            min_len = (min_len < n)? min_len:n;
            max_len = (max_len > n)? max_len:n;
        }
        std::cout << "maximum length of code = " << max_len << "\n";
        std::cout << "minimum length of code = " << min_len << "\n";
    }
    void Run() {
        // sort the array with its weight in non decreasing order
        std::sort(this->symbols.begin(), this->symbols.end(), [](const auto& a, const auto& b){ return (a->weight < b->weight);});
        //PrintNodes(v);
        auto root = BuildHuffmanTree(this->symbols);
        PrintCodes(root);
    }

};
# endif /*  HUFFMAN_CODES_H_ */