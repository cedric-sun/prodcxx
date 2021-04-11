/**
 *  dijkstra without the dist[] array.
 *
 *  If the graph has more than 1 component (i.e. disconnected graph),
 *  you need 1 more counter variable to detect that.
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
bool done[MAXN];

int main() {
    int n, m;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        // clean-up: be very careful about < or <=
        for (int i = 0; i <= n; ++i) {
            G[i].clear();
        }
        memset(done, 0, sizeof(done));
        // build graph: 2 edges if undirected graph
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            G[u].push_back({v, w});
            G[v].push_back({u, w});
        }
        priority_queue<snode> q;
        q.push({1, 0});
        int ans;
        while (!q.empty()) {
            snode cur = q.top();
            q.pop();
            if (done[cur.u])
                continue;
            for (const auto &e : G[cur.u]) {
                if (done[e.v])
                    continue;
                q.push({e.v, cur.d + e.w});
            }
            // cur.u settled permanently, shortest distance from S to cur.u is cur.d
            done[cur.u] = true;
            if (cur.u == n) {
                ans = cur.d;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
