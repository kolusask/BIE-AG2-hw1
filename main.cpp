#include <set>


struct Node {
    bool undef = false;
    unsigned disc, low;
    std::set<unsigned> adj;
};

using Graph = std::vector<Node>;

Neighbors read_input() {
    unsigned nNodes, nEdges;
    std::cin >> nNodes, nEdges;
    Neighbors result;
    result.reserve(nNodes);
    for (unsigned i = 0; i < nEdges; i++) {
        unsigned n1, n2;
        std::cin >> n1 >> n2;
        result[n1].adj.push_back(n2);
        result[n2].adj.push_back(n1);
    }
    return result;
}



int main() {

    return 0;
}
