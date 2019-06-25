import networkx as nx
import matplotlib.pyplot as plt

# line = input()
# v = int(line.split(' ')[0])
# e = int(line.split(' ')[1])

f = open('graph.txt', 'r')
lines = f.readlines()

line = lines[0].split(' ')
del lines[0]

v = int(line[0])
e = int(line[1])

G = nx.Graph()

edge_weights = {}

for i in range(e):
    # line = input()
    elements = lines[i].split(' ')
    e1 = int(elements[0])
    e2 = int(elements[1])
    w = int(elements[2])

    edge_weights[(e1, e2)] = w
    
    G.add_edge(e1, e2, weight=w)

closeness_map = nx.closeness_centrality(G, distance='weight')
closeness = []

for node in sorted(closeness_map):
    closeness.append(closeness_map[node])
    
nx.draw_planar(G, with_labels=True, node_color=closeness, node_size=2000, cmap=plt.cm.Reds, font_size=20, font_color='w')
nx.draw_networkx_edge_labels(G, pos=nx.planar_layout(G), edge_labels=edge_weights, font_size=10)
plt.show()
f.close()
