// plot twist: prim is just dijkstra with a different cost function
#include <bits/stdc++.h>

using namespace std;

struct adj {
    int v, weight;
};

struct snode {
    int u, min_e;

    bool operator<(const snode &rhs) const {
        return min_e > rhs.min_e;
    }
};

constexpr int MAXN = 1000;
vector<adj> G[MAXN];
bool done[MAXN];

// lc1584
class Solution {
public:
    int minCostConnectPoints(const vector<vector<int>> &points) {
        const int n = points.size();
        memset(done, false, sizeof done);
        for (int i = 0; i < n; ++i) {
            G[i].clear();
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; ++j) {
                const int d = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                G[i].push_back({j, d});
                G[j].push_back({i, d});
            }
        }
        priority_queue<snode> pq;
        pq.push({0, 0});
        int ans = 0;
        while (!pq.empty()) {
            snode cur = pq.top();
            pq.pop();
            if (done[cur.u])
                continue;
            done[cur.u] = true;
            ans += cur.min_e;
            for (const adj &e : G[cur.u]) {
                if (done[e.v])
                    continue;
                pq.push({e.v, e.weight});
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