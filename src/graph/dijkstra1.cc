/**
 * 1. Be careful that `int dist[]` could overflow;
 *      a) use long array instead or
 *      b) see dijkstra2 for omitting the dist array
 */

// hdu 2544
// vertex [1,n]
#include <bits/stdc++.h>

using namespace std;

struct adj {
    int v, w;
};

struct snode {
    int u, d; // use long for d if can overflow

    bool operator<(const snode &rhs) const {
        return d > rhs.d;
    }
};

#define MAXN 105
vector<adj> G[MAXN];
int dist[MAXN];

int main() {
    int n, m;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        // clean-up: be very careful about < or <=
        for (int i = 1; i <= n; ++i) {
            G[i].clear();
            dist[i] = INT_MAX;
        }
        dist[1] = 0;
        // build graph: 2 edges if undirected graph
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            G[u].push_back({v, w});
            G[v].push_back({u, w});
        }
        priority_queue<snode> q;
        q.push({1, 0});
        while (!q.empty()) {
            snode cur = q.top();
            q.pop();
            if (cur.d != dist[cur.u]) {// > should also work
                continue;
            }
            for (const auto &e : G[cur.u]) {
                int tmp = dist[cur.u] + e.w;
                if (tmp < dist[e.v]) {
                    dist[e.v] = tmp;
                    q.push({e.v, tmp});
                }
            }
            // cur.u settle permanently
            if (cur.u == n)
                break;
        }
        cout << dist[n] << endl;
    }
    return 0;
}
