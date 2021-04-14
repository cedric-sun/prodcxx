// hdu2066
#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1000;

#define MAX 0x7fffffff //数据很刁钻，我一开始写2100000000都过不了
int G[MAXN + 1][MAXN + 1];
bool done[MAXN + 1];
int dist[MAXN + 1];

int main() {
    int en, sn, dn;
    while (cin >> en >> sn >> dn) {
        for (int i = 1; i <= 1000; i++)
            for (int j = 1; j <= 1000; j++)
                G[i][j] = MAX;
        for (int i = 0; i < en; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            if (G[u][v] > w)
                G[u][v] = G[v][u] = w;//坑点所在：会有重复的边
        }
        vector<int> ss(sn), dd(dn);
        for (int &s :ss)
            cin >> s;
        for (int &d : dd)
            cin >> d;
        int ans = INT_MAX;
        for (int s : ss) {
            memset(done, false, sizeof(done));
            for (int i = 1; i <= 1000; i++)
                dist[i] = MAX;
            dist[s] = 0;
            while (true) {
                int u = -1;
                for (int i = 1; i <= 1000; i++) {
                    // ============ WARNING WARNING WARNING WARNING ============
                    //      `dist[i] != MAX` IS EXTREMELY IMPORTANT
                    //
                    //      WITHOUT IT, THE RUN TIME DROP FROM 62 ms TO 500 ms
                    //      AND THE PROGRAM IS VULNERABLE TO ARITHMETIC OVERFLOW!
                    // =========================================================
                    if (!done[i] && dist[i] != MAX && (u == -1 || dist[i] < dist[u])) {
                        u = i;
                    }
                }
                if (u == -1)
                    break;
                // now we've ensured u is accessible from s, so the following addition can't overflow
                done[u] = true;
                for (int v = 1; v <= 1000; v++) {
                    if (done[v] || G[u][v] == MAX)
                        continue;
                    int new_dist = dist[u] + G[u][v];
                    if (dist[v] > new_dist) {
                        dist[v] = new_dist;
                    }
                }
            }
            for (int d : dd) {
                ans = min(ans, dist[d]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
