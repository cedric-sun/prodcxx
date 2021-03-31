// topologically sort.
// given a directed graph
// 1. if ring is detected, abort; otherwise
// 2. produce an sequence of nodes whose order does not violate the "depends on" relationship

#include <cstring>
#include <vector>

using namespace std;

#define MAXN 100005

static char vis[MAXN];
//static vector<int> topo;
static vector<int> G[MAXN];
static bool has_ring;

void topo_dfs(int u) {
    vis[u] = -1; // visiting
    for (int v : G[u]) {
        if (vis[v] == -1) {
            has_ring = true;
            return;
        } else if (vis[v] == 0) { // unvisited
            topo_dfs(v);
            if (has_ring)
                return;
        }
    }
    vis[u] = 1;
    //topo.push_back(u);
}

int main() {
    // clean up before each test case
    int n = 123345; // the number of vertexes indexed [0,n-1]
    has_ring = false;
    for (int i = 0; i < numCourses; ++i) {
        G[i].clear();
    }
    memset(vis, UNVISITED, sizeof(vis));
    // ---------- build G from edge set if necessary -------------
    for (int u = 0; u < n; u++) {
        if (vis[u] == UNVISITED) {
            topo_dfs(u);
            if (has_ring) {
                // ring detected
                break;
            }
        }
    }
//    if (!has_ring) { // found answer
//        reverse(topo.begin(), topo.end());
//    }
}