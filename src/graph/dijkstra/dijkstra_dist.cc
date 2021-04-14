// hdu 2066
#include <bits/stdc++.h>

using namespace std;

struct adj {
    int v, weight;
};

struct snode {
    int vertex, culdist;

    bool operator<(const snode &rhs) const { return culdist > rhs.culdist; }
};

constexpr int MAXN = 1000;
int A[MAXN + 1][MAXN + 1];
vector<adj> G[MAXN + 1];
int dist[MAXN + 1];

int main() {
    int en, sn, dn;
    while (cin >> en >> sn >> dn) {
        memset(A, 0xff, sizeof A);
        int max_vid = -1;
        for (int i = 0; i < en; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            if (A[u][v] == -1 || A[u][v] > w)
                A[u][v] = A[v][u] = w;
            max_vid = max({max_vid, u, v});
        }
        for (int i = 1; i <= max_vid; ++i) {
            G[i].clear();
            for (int j = 1; j <= max_vid; ++j) {
                if (A[i][j] != -1)
                    G[i].push_back({j, A[i][j]});
            }
        }
        vector<int> ss(sn), dd(dn);
        for (int &s : ss)
            cin >> s;
        for (int &d : dd)
            cin >> d;
        int ans = numeric_limits<int>::max();
        for (int s : ss) {
            memset(dist, 0x7f, sizeof dist);
            priority_queue<snode> pq;
            pq.push({s, 0});
            // no need to dist[s] = 0;
            while (!pq.empty()) {
                int u = pq.top().vertex;
                int culdist = pq.top().culdist;
                pq.pop();
                if (culdist > dist[u]) {
                    continue;
                }
                dist[u] = culdist;
                for (const adj &e : G[u]) {
                    int tmp = culdist + e.weight;
                    if (tmp < dist[e.v]) {
                        //no need to dist[e.v] = tmp;
                        pq.push({e.v, tmp});
                    }
                }
            }
            for (int d : dd)
                ans = min(ans, dist[d]);
        }
        cout << ans << endl;
    }
    return 0;
}
