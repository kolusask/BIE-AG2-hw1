import networkx as nx

graph = nx.Graph()
with open("input.txt") as file:
    edges = int(file.readline().split()[1])
    for e in range(edges):
        u, v = (int(i) for i in file.readline().split())
        graph.add_edge(u, v)
    
subgraphs = list(graph.subgraph(c) for c in nx.biconnected_components(graph))
for sub in subgraphs:
    print(sub.edges())
    try:
        cycle = nx.cycle_basis(graph)
        print(cycle)
    except:
        print("NO")
    print("")
