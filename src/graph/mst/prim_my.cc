#include <bits/stdc++.h>

using namespace std;

struct edge {
    int u, v, weight;

    bool operator<(const edge &rhs) const { return weight < rhs.weight; }
};

constexpr int MAXN = 1000;

struct adj {
    int v, weight;
};

vector<adj> G[MAXN];
bool done[MAXN];

class Solution {
public:
    int minCostConnectPoints(const vector<vector<int>> &points) {
        const int n = points.size(); // vertex [0,n-1]
        memset(done, false, sizeof done);
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int d = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][0]);
                G[i].push_back({j, d});
                G[j].push_back({i, d});
            }
        }
        priority_queue<edge> pq;
        int s = 0;
        for (const adj &a : G[s]) {
            pq.push({s, a.v, a.weight});
        }
        done[s] = true;
        while (!pq.empty()) {
            edge min_edge = pq.top();
            pq.pop();
            if (/*min_edge does not connect the tree to a vertex outside the tree*/) {
                continue; // ignore the edge
            }

        }
    }
};