#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <vector>

#define INF 10000
#define UNDEF 0

struct Node {
    void insert_child(const int child) { children.insert(child); }
    unsigned in = UNDEF, low = INF;
    unsigned in2 = UNDEF;
    std::set<unsigned> adj;
    std::set<unsigned> children;
};

using NodeSet = std::set<unsigned>;
using Edge = std::pair<unsigned, unsigned>;
using EdgeSet = std::set<Edge>;


class Graph {
  public:
    Graph(const unsigned nNodes, const EdgeSet& edges) : mNodes(nNodes) {
        for (const Edge& edge : edges) {
            mNodes[edge.first].adj.insert(edge.second);
            mNodes[edge.second].adj.insert(edge.first);
        }
    }
    unsigned size() const { return mNodes.size(); }
    Node& operator[](const unsigned ind) { return mNodes[ind]; }
    void refresh() {
        for (auto& node : mNodes)
            node.in2 = UNDEF;
    }

  private:
    std::vector<Node> mNodes;
};

Graph read_input() {
    unsigned nNodes, nEdges;
    std::cin >> nNodes >> nEdges;
    EdgeSet edges;
    for (unsigned i = 0; i < nEdges; i++) {
        unsigned n1, n2;
        std::cin >> n1 >> n2;
        edges.insert(Edge(n1, n2));
    }
    return Graph(nNodes, edges);
}

unsigned count = 0;



bool has_odd_cycles(Graph& graph, const EdgeSet& edges) {
    // use BFS here!
}

void dfs(Graph& graph, const unsigned node, const unsigned parent, std::list<Edge>& st, std::vector<EdgeSet>& bc) {
    graph[node].in = ++count;
    for (unsigned ch : graph[node].adj) {
        if (graph[ch].in == UNDEF) {
            graph[node].insert_child(ch);
            st.push_back(Edge(node, ch));
            dfs(graph, ch, node, st, bc);
            if (graph[ch].low >= graph[node].in && (parent != INF || graph[node].children.size() > 1)) {
                EdgeSet connEdges;
                while (st.back().first != node || st.back().second != ch) {
                    connEdges.insert(st.back());
                    connEdges.insert(Edge(st.back().second, st.back().first));
                    st.pop_back();
                }
                connEdges.insert(st.back());
                connEdges.insert(Edge(st.back().second, st.back().first));
                st.pop_back();
                bc.push_back(connEdges);
            }
            graph[node].low = std::min(graph[node].low, graph[ch].low);
        } else if (graph[ch].in < graph[node].in && ch != parent) {
            graph[node].low = std::min(graph[node].low, graph[ch].in);
            if (graph[ch].in < graph[node].in)
                st.push_back(Edge(node, ch));
        }
    }
}

NodeSet nodes_from_edges(const EdgeSet& edges) {
    NodeSet nodes;
    for (Edge e : edges) {
        nodes.insert(e.first);
        nodes.insert(e.second);
    }
    return nodes;
}

EdgeSet biconnected_edges(Graph& graph) {
    std::vector<EdgeSet> result;
    std::list<Edge> edgeStack;
    for (unsigned i = 0; i < graph.size(); i++) {
        if (graph[i].in == UNDEF) {
            dfs(graph, i, INF, edgeStack, result);
            EdgeSet edgeSet;
            while (edgeStack.size() > 0) {
                edgeSet.insert(edgeStack.back());
                edgeSet.insert(Edge(edgeStack.back().second, edgeStack.back().first));
                edgeStack.pop_back();
            }
            if (!edgeSet.empty())
                result.push_back(edgeSet);
        }
    }
    if (result.empty())
        return EdgeSet();
    std::sort(
        result.begin(),
        result.end(),
        [](const EdgeSet& es1, const EdgeSet& es2) -> bool {
            return nodes_from_edges(es1).size() < nodes_from_edges(es2).size();
        }
    );
    while (!result.empty() && has_odd_cycles(graph, result.back()))
        result.pop_back();
    return result.empty() ? EdgeSet() : result.back();
}

int main() {
    auto graph = read_input();
    auto edges = biconnected_edges(graph);
    auto nodes = nodes_from_edges(edges);
    std::cout << nodes.size() << std::endl;
    for (unsigned node : nodes)
        std::cout << node << ' ';
    if (!nodes.empty())
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
    ---
    12 14
    0 1
    0 6
    1 2
    1 3
    2 3
    3 4
    2 4
    1 5
    5 6
    5 7
    7 8
    5 8
    8 9
    10 11
    ---
    6 8
    0 1
    1 2
    2 3
    2 5
    5 4
    2 4
    1 4
    0 3
    ---
    18 26
    0 1
    1 2
    2 3
    1 3
    1 4
    4 6
    5 6
    1 5
    4 5
    7 11
    11 12
    7 13
    13 12
    7 14
    14 12
    15 9
    9 16
    16 17
    17 9
    6 7
    7 8
    8 9
    10 6
    10 7
    10 8
    10 9
    ---
    
*/
