#include <iostream>
#include <set>
#include <vector>

#define INF 10000
#define UNDEF 0

struct Node {
    unsigned in = UNDEF, low = INF;
    std::set<unsigned> adj;
    std::set<unsigned> children;
};

using Graph = std::vector<Node>;

Graph read_input() {
    unsigned nNodes, nEdges;
    std::cin >> nNodes >> nEdges;
    Graph result(nNodes);
    for (unsigned i = 0; i < nEdges; i++) {
        unsigned n1, n2;
        std::cin >> n1 >> n2;
        result[n1].adj.insert(n2);
        result[n2].adj.insert(n1);
    }
    return result;
}

unsigned count = 0;

void dfs(Graph& graph, const unsigned node, const unsigned parent, std::set<unsigned>& acc) {
    graph[node].in = ++count;
    for (unsigned ch : graph[node].adj) {
        if (graph[ch].in == UNDEF) {
            graph[node].children.insert(ch);
            dfs(graph, ch, node, acc);
            if (graph[ch].low >= graph[node].in && (parent != INF || graph[node].children.size() > 1)) {
                acc.insert(node);
            }
            graph[node].low = std::min(graph[node].low, graph[ch].low);
        } else if (graph[ch].in < graph[node].in && ch != parent)
            graph[node].low = std::min(graph[node].low, graph[ch].in);
    }
}

std::set<unsigned> find_articulation_points(Graph& graph) {
    std::set<unsigned> result;
    dfs(graph, 0, INF, result);
    return result;
}

int main() {
    auto graph = read_input();
    for (auto p : find_articulation_points(graph))
        std::cout << p << ' ';
    std::cout << std::endl;
    return 0;
}

/*
    9 10
    0 1
    1 2
    2 3
    3 4
    4 0
    2 5
    6 5
    8 5
    7 8
    6 7
    ---
    4 6
    0 1
    2 0
    0 3
    2 1
    3 2
    1 3
    ---
    10 11
    0 1
    1 2
    2 3
    2 5
    8 2
    3 5
    7 5
    3 4
    6 7
    7 8
    9 8
*/
