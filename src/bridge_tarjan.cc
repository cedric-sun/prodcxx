// cesun, 9/16/20 11:05 AM.

#include <vector>

using std::vector;
using std::min;

#define MAXN 100005

int low[MAXN], dfn[MAXN], dfs_clock;
vector<int> G[MAXN];
vector<vector<int>> ans;

void tarjan(int u, int fa) {
    low[u] = dfn[u] = ++dfs_clock;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                ans.push_back({u, v});
            }
        } else if (dfn[v] < dfn[u] && v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

#include <cstring>
void clear() {
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    ans.clear();
    dfs_clock=0;
    for (int i = 0; i < MAXN; ++i) {
        G[i].clear();
    }
}

// test: https://leetcode.com/problems/critical-connections-in-a-network/
class Solution {
public:
    vector<vector<int>> criticalConnections(int n,const vector<vector<int>>& connections) {
        clear();
        for (const vector<int> &e : connections) {
            G[e[0]].push_back(e[1]);
            G[e[1]].push_back(e[0]);
        }
        tarjan(0, -1);
        return ans;
    }
};