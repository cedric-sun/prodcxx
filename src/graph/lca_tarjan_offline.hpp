// cesun, 9/6/20 10:44 PM.

// offline refers to the fact that all queries must be known before the algorithm begins

#include <algorithm>
#include <vector>
#include "../ds/disjoint-set.hpp"

int ancestor[MAXN];
bool visited[MAXN];
vector<int> G[MAXN];
vector<int> Queries[MAXN];

static void lca_tarjan(int u) {
    // ancestor[u] = u; // TODO: is this necessary?
    for (int v : G[u]) {
        lca_tarjan(v);
        ds_join(u, v);
        ancestor[ds_find(u)] = u; // refresh ancestor of the whole group (group leader)
        // since the group leader might change in ds_join()
    }
    visited[u] = true;
    for (int v : Queries[u]) {
        if (visited[v]) {
            // LCA of u and v is ancestor[ds_find(v)]
        }
    }
}

static void lca_init(int n) {
    ds_init(n);
    memset(visited, 0, n);
    // build G
}



