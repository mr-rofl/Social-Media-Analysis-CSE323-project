import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import os

def draw(G, pos, measures, weights, measure_name):
    
    nodes = nx.draw_networkx_nodes(G, pos, cmap=plt.cm.rainbow, 
                                   node_color=list(measures.values()),
                                   nodelist=list(measures.keys()),
                                   node_size=1000,
                                   font_size=20, font_color='w')
    
    nodes.set_norm(mcolors.SymLogNorm(linthresh=0.01, linscale=1))
    weights = nx.draw_networkx_edge_labels(G, pos, edge_labels = weights)
    labels = nx.draw_networkx_labels(G, pos)
    edges = nx.draw_networkx_edges(G, pos)

    plt.title(measure_name)
    plt.colorbar(nodes)
    plt.axis('off')
    plt.show()
direct='C:/Users/ROFL/Documents/GitHub/Social-Media-Analysis-CSE323-project'
f = open(direct+'/graph.txt', 'r')
lines = f.readlines()



G = nx.Graph()

edge_weights = {}

for line in lines:
    elements = line.split(' ')
    e1 = int(elements[0])
    e2 = int(elements[1])
    w = int(elements[2])

    edge_weights[(e1, e2)] = w
    
    G.add_edge(e1, e2, weight=w)

degree = nx.degree_centrality(G)
closeness = nx.closeness_centrality(G, distance='weight')
betweenness = nx.betweenness_centrality(G, weight='weight')

draw(G, nx.circular_layout(G), degree, edge_weights, "Degree Centrality")
draw(G, nx.circular_layout(G), closeness, edge_weights, "Closeness Centrality")
draw(G, nx.circular_layout(G), betweenness, edge_weights, "Betweenness Centrality")

f.close()
