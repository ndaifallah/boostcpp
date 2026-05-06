#include <iostream>
#include <string>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>

// ============================================================
// EXERCISE 8: Boost Graph Library (BGL)
// ============================================================

// CONCEPT: adjacency_list - The most commonly used graph type
// - Template parameters: OutEdgeList, VertexList, Directedness
// - vecS uses std::vector for storage (fast, compact)
// - listS uses std::list (stable vertex/edge descriptors)
// - directedS / undirectedS for edge direction
// - Bundled properties can be attached to vertices and edges

void example_basic_graph() {
    std::cout << "\n=== Basic Graph Creation ===\n";

    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;

    Graph g(5);

    boost::add_edge(0, 1, g);
    boost::add_edge(0, 2, g);
    boost::add_edge(1, 3, g);
    boost::add_edge(2, 3, g);
    boost::add_edge(3, 4, g);
    boost::add_edge(1, 4, g);

    std::cout << "Graph with 5 vertices and " << boost::num_edges(g) << " edges\n";
    std::cout << "Vertices: " << boost::num_vertices(g) << "\n";

    for (auto v = boost::vertices(g); v.first != v.second; ++v.first) {
        auto outEdges = boost::out_edges(*v.first, g);
        std::cout << "Vertex " << *v.first << " -> ";
        for (auto e = outEdges.first; e != outEdges.second; ++e) {
            std::cout << boost::target(*e, g) << " ";
        }
        std::cout << "\n";
    }
}

// CHALLENGE 8.1: Create an undirected graph with 4 vertices.
// Add edges: (0,1), (1,2), (2,3), (3,0) to form a cycle.
// Print all vertices and their neighbors.
void challenge_basic_graph() {
    std::cout << "\n--- Challenge 8.1: Undirected cycle graph ---\n";

    // TODO: Create an undirected adjacency_list with 4 vertices

    // TODO: Add edges (0,1), (1,2), (2,3), (3,0)

    // TODO: Print each vertex and its neighbors

    std::cout << "Challenge 8.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Breadth-First Search (BFS)
// - Explores graph level by level from a source vertex
// - Uses a visitor pattern for callbacks
// - Useful for shortest path in unweighted graphs, level-order traversal

struct BfsDistanceVisitor : public boost::default_bfs_visitor {
    int* dist;

    explicit BfsDistanceVisitor(int* d) : dist(d) {}

    template <typename Edge, typename Graph>
    void tree_edge(Edge e, const Graph& g) const {
        auto u = boost::source(e, g);
        auto v = boost::target(e, g);
        dist[v] = dist[u] + 1;
    }
};

void example_bfs() {
    std::cout << "\n=== Breadth-First Search ===\n";

    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
    Graph g(6);

    boost::add_edge(0, 1, g);
    boost::add_edge(0, 2, g);
    boost::add_edge(1, 3, g);
    boost::add_edge(2, 3, g);
    boost::add_edge(3, 4, g);
    boost::add_edge(4, 5, g);
    boost::add_edge(2, 5, g);

    std::vector<int> dist(boost::num_vertices(g), 0);

    std::cout << "BFS from vertex 0:\n";
    boost::breadth_first_search(g, 0,
        boost::visitor(BfsDistanceVisitor(dist.data())));

    for (size_t i = 0; i < dist.size(); ++i) {
        std::cout << "  Vertex " << i << " at distance " << dist[i] << "\n";
    }
}

// CHALLENGE 8.2: Create a graph representing a social network:
//   Alice(0) -> Bob(1), Charlie(2)
//   Bob(1) -> Diana(3)
//   Charlie(2) -> Diana(3), Eve(4)
//   Diana(3) -> Eve(4)
// Run BFS from Alice (0) and print the distance to each person.
void challenge_bfs() {
    std::cout << "\n--- Challenge 8.2: Social network BFS ---\n";

    // TODO: Create a directed graph with 5 vertices

    // TODO: Add edges representing the social network above

    // TODO: Run BFS from vertex 0 (Alice) using a distance visitor

    // TODO: Print the distance from Alice to each person

    std::cout << "Challenge 8.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Depth-First Search (DFS)
// - Explores as far as possible along each branch before backtracking
// - Provides discover_vertex, finish_vertex, examine_edge events
// - Useful for cycle detection, topological sort, path finding

struct DfsPrintVisitor : public boost::default_dfs_visitor {
    template <typename Vertex, typename Graph>
    void discover_vertex(Vertex v, const Graph&) const {
        std::cout << "  Discovered vertex " << v << "\n";
    }
};

void example_dfs() {
    std::cout << "\n=== Depth-First Search ===\n";

    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
    Graph g(4);

    boost::add_edge(0, 1, g);
    boost::add_edge(0, 2, g);
    boost::add_edge(1, 2, g);
    boost::add_edge(2, 0, g);
    boost::add_edge(2, 3, g);
    boost::add_edge(3, 3, g);

    std::cout << "DFS vertex discovery order:\n";
    boost::depth_first_search(g, boost::visitor(DfsPrintVisitor()));
}

// CHALLENGE 8.3: Create a graph and use DFS to record the finish times of vertices.
// Vertices: 0,1,2,3 with edges: (0,1), (0,2), (1,3), (2,3)
// Use a visitor to print when each vertex finishes.
void challenge_dfs() {
    std::cout << "\n--- Challenge 8.3: DFS finish times ---\n";

    // TODO: Create a directed graph with 4 vertices

    // TODO: Add edges (0,1), (0,2), (1,3), (2,3)

    // TODO: Define a custom DFS visitor that prints finish_vertex events

    // TODO: Run DFS with your custom visitor

    std::cout << "Challenge 8.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Dijkstra Shortest Path
// - Finds shortest paths from a source in weighted graphs
// - Requires non-negative edge weights
// - Returns distance map and predecessor map

void example_dijkstra() {
    std::cout << "\n=== Dijkstra Shortest Path ===\n";

    struct EdgeProp { double weight; };
    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                        boost::no_property, EdgeProp>;

    Graph g(5);

    boost::add_edge(0, 1, {4.0}, g);
    boost::add_edge(0, 2, {2.0}, g);
    boost::add_edge(1, 3, {5.0}, g);
    boost::add_edge(2, 1, {1.0}, g);
    boost::add_edge(2, 3, {8.0}, g);
    boost::add_edge(2, 4, {10.0}, g);
    boost::add_edge(3, 4, {3.0}, g);

    std::vector<double> dist(boost::num_vertices(g));
    std::vector<int> pred(boost::num_vertices(g));

    auto indexMap = boost::get(boost::vertex_index, g);
    auto weightMap = boost::get(&EdgeProp::weight, g);

    boost::dijkstra_shortest_paths(g, 0,
        boost::predecessor_map(&pred[0])
        .distance_map(&dist[0])
        .vertex_index_map(indexMap)
        .weight_map(weightMap));

    std::cout << "Shortest distances from vertex 0:\n";
    for (size_t i = 0; i < dist.size(); ++i) {
        std::cout << "  Vertex " << i << ": " << dist[i] << "\n";
    }

    std::cout << "Path to vertex 4: ";
    int v = 4;
    std::vector<int> path;
    while (v != 0) {
        path.push_back(v);
        v = pred[v];
    }
    path.push_back(0);
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        std::cout << *it << (it == path.rbegin() ? "" : " -> ");
    }
    std::cout << "\n";
}

// CHALLENGE 8.4: Create a weighted graph of cities:
//   0(A) -> 1(B): 7,  0(A) -> 2(C): 9,  0(A) -> 3(F): 14
//   1(B) -> 2(C): 10, 1(B) -> 3(F): 15
//   2(C) -> 3(F): 11, 2(C) -> 4(D): 2
//   3(F) -> 4(D): 9
// Run Dijkstra from A(0) and find shortest path to D(4).
void challenge_dijkstra() {
    std::cout << "\n--- Challenge 8.4: City distances ---\n";

    // TODO: Define EdgeProp with weight and create weighted directed graph

    // TODO: Add all city edges with their distances

    // TODO: Run Dijkstra from vertex 0 (city A)

    // TODO: Print shortest distances to all cities

    // TODO: Reconstruct and print the path from A to D using predecessor map

    std::cout << "Challenge 8.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Topological Sort
// - Linear ordering of vertices such that for every edge (u,v), u comes before v
// - Only works on DAGs (Directed Acyclic Graphs)
// - Useful for task scheduling, build systems, dependency resolution

void example_topological_sort() {
    std::cout << "\n=== Topological Sort ===\n";

    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
    Graph g(6);

    boost::add_edge(5, 2, g);
    boost::add_edge(5, 0, g);
    boost::add_edge(4, 0, g);
    boost::add_edge(4, 1, g);
    boost::add_edge(2, 3, g);
    boost::add_edge(3, 1, g);

    std::vector<int> topo_order;

    boost::topological_sort(g, std::back_inserter(topo_order));

    std::cout << "Topological order (reversed for display):\n";
    for (auto it = topo_order.rbegin(); it != topo_order.rend(); ++it) {
        std::cout << "  " << *it << " ";
    }
    std::cout << "\n";
}

// CHALLENGE 8.5: Create a DAG representing course prerequisites:
//   CS101(0) -> CS201(1)
//   CS101(0) -> CS102(2)
//   CS102(2) -> CS202(3)
//   CS201(1) -> CS301(4)
//   CS202(3) -> CS301(4)
// Run topological sort to find a valid order to take courses.
void challenge_topological_sort() {
    std::cout << "\n--- Challenge 8.5: Course prerequisites ---\n";

    // TODO: Create a DAG with 5 vertices (courses 0-4)

    // TODO: Add prerequisite edges as described above

    // TODO: Run topological sort

    // TODO: Print the valid course ordering

    std::cout << "Challenge 8.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Connected Components
// - Groups vertices that can reach each other
// - For undirected graphs: finds disconnected subgraphs
// - Returns component count and assigns component ID to each vertex

void example_connected_components() {
    std::cout << "\n=== Connected Components ===\n";

    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
    Graph g(7);

    boost::add_edge(0, 1, g);
    boost::add_edge(1, 2, g);
    boost::add_edge(2, 0, g);

    boost::add_edge(3, 4, g);
    boost::add_edge(4, 5, g);

    boost::add_edge(6, 6, g);

    std::vector<int> component(boost::num_vertices(g));
    int num = boost::connected_components(g, &component[0]);

    std::cout << "Number of connected components: " << num << "\n";
    for (size_t i = 0; i < component.size(); ++i) {
        std::cout << "  Vertex " << i << " in component " << component[i] << "\n";
    }
}

// CHALLENGE 8.6: Create an undirected graph with 8 vertices and these edges:
//   (0,1), (1,2), (2,3), (4,5), (5,6), (7,7)
// Find connected components and print how many groups exist.
// For each component, list which vertices belong to it.
void challenge_connected_components() {
    std::cout << "\n--- Challenge 8.6: Group vertices by component ---\n";

    // TODO: Create undirected graph with 8 vertices

    // TODO: Add edges (0,1), (1,2), (2,3), (4,5), (5,6), (7,7)

    // TODO: Find connected components

    // TODO: Print the number of components

    // TODO: For each component, list its vertices

    std::cout << "Challenge 8.6 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_boost_graph() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 8: Boost Graph Library (BGL)\n";
    std::cout << "========================================\n";

    example_basic_graph();
    challenge_basic_graph();

    example_bfs();
    challenge_bfs();

    example_dfs();
    challenge_dfs();

    example_dijkstra();
    challenge_dijkstra();

    example_topological_sort();
    challenge_topological_sort();

    example_connected_components();
    challenge_connected_components();

    std::cout << "\n========================================\n";
    std::cout << "Boost Graph exercise complete!\n";
    std::cout << "========================================\n";
}
