# ifndef TWO_SAT_H_
# define TWO_SAT_H_
# include "kosaraju.h"
/**
 * @brief check weather clauses were satisfiable
example:
 * int main ()
{
    TwoSAT test;
    const std::string file_name = "../data/2sat/_02c1945398be467219866ee1c3294d2d_2sat";
    for (int i = 1; i <= 6; ++i) {
        std::cout << test.Satisfiable(file_name + std::to_string(i) + ".txt");
    }
    std::cout << "\n";
    return 0;
} 
 */
class TwoSAT {
private:
    int size; // the number of variables and the number of clauses is the same
    Graph g;
    Graph g_rev;
public:
    /**
     * @brief In each instance, the number of variables and the number of clauses is the same, 
     * and this number is specified on the first line of the file.  
     * 
     * @param line 
     */
    void ProcessHeader (std::string& line) {
        this->size = std::stoi(line);
        // each variable represent 2 vertices, graph[x] for x and graph[n-(-x)] for ~x 
        Graph new_g;
        Graph new_g_rev;
        this->g.swap(new_g);
        this->g_rev.swap(new_g_rev);
        this->g.resize(this->size * 2 + 1);
        this->g_rev.resize(this->size * 2 + 1);
        //std::cout << "reset size to " << this->g.size() << "\n";
    }
    /**
     * @brief Each subsequent line specifies a clause via its two literals, with a number denoting
     *  the variable and a "-" sign denoting logical "not".  For example, "-16808 75250" indicates
     *  the clause ¬x16808 V x75250​.
     * 
     * @param line 
     */
    void ProcessLine (std::string& line) {
        int a,b;
        std::istringstream ss(line);
        ss >> a >> b;
        AddEdge(-a, b);
        AddEdge(-b, a);
    }
    void AddEdge(int from, int to) {
        int from_vertex = (from > 0) ? from : -from + this->size;
        int to_vertex = (to > 0) ? to : -to + this->size;
        try {
            this->g[from_vertex].emplace_back(to_vertex);
        }
        catch (...) {
            std::cout << "from vertex " << from_vertex <<  " out of range\n";
        }
        try {
            this->g_rev[to_vertex].emplace_back(from_vertex);
        }
        catch (...) {
            std::cout << "to vertex " << to_vertex <<  " out of range\n";
        }
    }
    /**
     * @brief use scc method to check if input clauses is satisfiable
     * 
     * @param clauses_file 
     * @return true 
     * @return false 
     */
    bool Satisfiable(const std::string& clauses_file) {
        if (!ReadData(clauses_file, true, *this))
            std::cout << "fail reading data.\n";
        Kosaraju scc(this->size * 2);
        scc.findSCC(this->g, this->g_rev);
        // if a and ~a are in the same scc than it's not satisfiable
        for (int i = 1; i <= this->size; ++i) {
            if (scc.FindLeader(i) == scc.FindLeader(i + this->size)) {
                // std::cout << "vertex " << i << " with leader " << scc.FindLeader(i) << " not satisfiable\n"; 
                return false;
            }
        }
        return true;
    }
};
# endif /* TWO_SAT_H_ */