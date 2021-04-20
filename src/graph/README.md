#### Dijkstra
1. Dijkstra can't work on graph with negative edge weight. This is due to the fact that dijkstra has the concept of settling points and not considering it again. 
https://stackoverflow.com/questions/13159337/why-doesnt-dijkstras-algorithm-work-for-negative-weight-edges
2. Dijkstra is more like a generic framework based on relaxation. Finding single source shortest path is only one application.

#### Dijkstra and MinST on UNDIRECTED graph
The following discussion applies only for undirected graph, since
MinST/MaxST on a directed graph is undefined.

1. The predecessor subgraph formed by dijkstra's algorithm
does not produce a minimum spanning tree. (https://stackoverflow.com/a/20482220/8311608)

2. But by simply modifying the cost function of dijkstra from
`d[v] = min(d[v], d[u] + e[u,v])` to `d[v] = min(d[v], e[u,v])`,
you get the prim's algorithm. This feels exactly like you are
using dijkstra to solve the widest path problem (again, on undirected graph)
   (see lc1631), which demonstrate again the relationship between MST and widest path problem:
    
    1. The widest path **from any source to any destination** are embeded in the MST.

The above discussion applies as well for the minimax path problem and MaxST.

#### Modified Dijkstra (prim relax) on **directed** graph

Even on directed graph, the prim relax dijkstra is useful to find single-source-all-destination widest path.

see https://leetcode.com/problems/path-with-maximum-minimum-value/

#### Questions to ask yourself for every graph problem
1. directed or undirected?
2. is it connected graph? how many component?
3. does negative weight edge exist?
4. how large is large enough for INF?
5. (for both directed and undirected graph) Does cycle exist?
