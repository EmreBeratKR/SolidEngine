import os
import re
import networkx as nx
import matplotlib.pyplot as plt
from collections import defaultdict
from matplotlib.colors import LinearSegmentedColormap

TITLE = "Header Files Dependency Visualizer"
SRC_DIR = "src"
FONT_SIZE = 15


def find_dependencies(directory):
    dependencies = {}
    
    for root, dirs, files in os.walk(directory):
        for filename in files:
            if filename.endswith(".h"):
                with open(os.path.join(root, filename), 'r') as file:
                    content = file.read()
                    # Find #include lines that are not commented out
                    include_matches = re.findall(r'^\s*#include\s+"([^"]+)"', content, re.MULTILINE)
                    if include_matches:
                        dependencies[filename] = include_matches
    
    return dependencies


def count_usage(dependencies):
    usage_count = defaultdict(int)
    
    for includes in dependencies.values():
        for dependency in includes:
            usage_count[dependency] += 1
            
    return usage_count


def visualize_dependencies(directory, font_size=10):
    dependencies = find_dependencies(directory)
    usage_count = count_usage(dependencies)
    
    G = nx.DiGraph()
    
    for file, includes in dependencies.items():
        G.add_node(file)
        for dependency in includes:
            G.add_edge(file, dependency)
    
    # Check for cycles (circular dependencies)
    cycles = list(nx.simple_cycles(G))
    
    # Create grid layout
    pos = {}
    count = 0
    for file in G.nodes():
        pos[file] = (count % 5, -count // 5)  # Adjust the grid size as needed
        count += 1
    
    # Compute node size based on label length
    node_size = {file: 2000 + 200 * len(file) for file in G.nodes()}
    
    # Compute font size based on label length
    max_label_length = max(len(file) for file in G.nodes())
    font_size = max(8, font_size - max(0, (max_label_length - 10) * 0.5))
    
    # Interpolate color map from green to red
    cmap = LinearSegmentedColormap.from_list("green_to_red", ["green", "red"])
    max_usage = max(usage_count.values())
    color_map = {file: cmap(usage_count[file] / max_usage) for file in G.nodes()}
    
    plt.figure(figsize=(10, 8))

    title = TITLE

    # Draw edges
    nx.draw_networkx_edges(G, pos, alpha=0)

    # Highlight circular dependencies
    if cycles:
        circular_nodes = set(node for cycle in cycles for node in cycle)
        circular_edges = [(cycle[i % len(cycle)], cycle[(i+1) % len(cycle)]) for cycle in cycles for i in range(len(cycle))]
        nx.draw_networkx_edges(G, pos, edgelist=circular_edges, edge_color='purple', width=2.0)
        nx.draw_networkx_nodes(G, pos, nodelist=circular_nodes, node_color='purple', node_size=3000)
        
        # Draw labels for circular dependent nodes
        labels = {file: f"{file.replace('_', '\n')}\n({usage_count[file]})" for file in circular_nodes}
        nx.draw_networkx_labels(G, pos, labels, font_size=font_size, font_weight="bold")
        title = f"{TITLE}\n\nCircular Dependencies: {len(cycles)}"
    else:
        # Draw labels for all nodes
        labels = {file: f"{file.replace('_', '\n')}\n({usage_count[file]})" for file in G.nodes()}
        nx.draw(G, pos, with_labels=False, node_size=list(node_size.values()), node_color=list(color_map.values()), arrowsize=20)
        nx.draw_networkx_labels(G, pos, labels, font_size=font_size, font_weight="bold")
    
    plt.title(title, fontweight="bold")
    plt.show()






if __name__ == "__main__":
    visualize_dependencies(SRC_DIR, FONT_SIZE)
