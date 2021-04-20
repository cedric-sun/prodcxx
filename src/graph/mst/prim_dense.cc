// This variant of the prim's algorithm runs in O(|V|^2) by NOT storing edges in priority_queue or set.
// Its complexity does not depend on the # of edges, thus performs good on dense graph, e.g. Euclidean MST.
// https://en.wikipedia.org/wiki/Euclidean_minimum_spanning_tree
// See https://leetcode.com/problems/min-cost-to-connect-all-points/

// Well honestly this implementation of Prim is just a modified version of dijkstra with adj matrix.

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1000;

int G[MAXN][MAXN]; // adjacency matrix; for dense graph, adj list degrades to adj matrix.
int pe[MAXN]; // pre_edge[i]: length of the shortest edge connecting vertex i and the current tree
bool done[MAXN]; // if in tree

// lc1584
class Solution {
public:
    int minCostConnectPoints(const vector<vector<int>> &points) {
        const int n = points.size();
        // we have a complete graph here so no need to memset G; for non-complete graph do this
        // memset(G,0x7f,sizeof G);
        memset(done, false, sizeof done);
        memset(pe, 0x7f, sizeof pe);
        // build graph O(|V|^2)
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                const int d = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                G[i][j] = G[j][i] = d;
            }
        }

        pe[0] = 0;
        int ans = 0;
        for (int i = 0; i < n; ++i) { // 1 vertex done in each loop
            int u = -1;
            for (int j = 0; j < n; ++j) {
                // pe[j] != 0x7f7f7f7f to avoid getting trapped by disconnected graph
                if (!done[j] && pe[j] != 0x7f7f7f7f && (u == -1 || pe[j] < pe[u]))
                    u = j;
            }
            if (u == -1) {
                break; // all vertexes in tree
            }
            done[u] = true;
            // add pe[u] to mst, update mst edge sum or min edge, etc...
            ans += pe[u];
            for (int v = 0; v < n; ++v) {
                // again, graph is complete for this question; uncomment G[u][v] == 0x7f7f7f7f for generic dense prim
                if (done[v] /*|| G[u][v] == 0x7f7f7f7f*/)
                    continue;
                pe[v] = min(G[u][v], pe[v]);
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    int ans = s.minCostConnectPoints({{0, 0},
                                      {2, 2},
                                      {3, 10},
                                      {5, 2},
                                      {7, 0}});
    cout << ans << endl;
    return 0;
}