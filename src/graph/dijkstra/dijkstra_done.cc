// lc 505

// Dijkstra on implicit state transfering graph.
// When you realize that dijkstra is heuristic BFS,
// and BFS is silly dijkstra and brute-force

#include <bits/stdc++.h>
using namespace std;

// maze min 1x1 ; max 100x100
constexpr int MAXN = 100;
// up right down left
constexpr int di[] = {-1, 0, 1, 0};
constexpr int dj[] = {0, 1, 0, -1};

struct ij {
    int i, j;
    bool operator==(const ij &rhs) const {
        return i==rhs.i && j == rhs.j;
    }
};

struct snode {
    ij x;
    int culdist;
    bool operator<(const snode &rhs) const { return culdist > rhs.culdist; }
};

struct adj {
    ij to;
    int len;
};

bool done[MAXN][MAXN];
int rn, cn;

adj hit(const vector<vector<int>> &maze, ij from, int drct) {
    int len = 0;
    ij tmp;
    while (tmp = {from.i + di[drct], from.j + dj[drct]},
            tmp.i >= 0 && tmp.i < rn && tmp.j >= 0 && tmp.j < cn &&
            maze[tmp.i][tmp.j] == 0) {
        from = tmp;
        len++;
    }
    return {from, len};
}

class Solution {
public:
    int shortestDistance(const vector<vector<int>> &maze,
                         const vector<int> &start,
                         const vector<int> &destination) {
        rn = maze.size(), cn = maze[0].size();
        const ij s{start[0], start[1]}, d{destination[0], destination[1]};
        memset(done, false, sizeof done);

        priority_queue<snode> pq;
        pq.push({s, 0});

        int ans = INT_MAX;
        while (!pq.empty()) {
            snode cur = pq.top();
            pq.pop();
            if (done[cur.x.i][cur.x.j])
                continue;
            done[cur.x.i][cur.x.j] = true;
            if (cur.x == d)
                ans = min(ans, cur.culdist);
            for (int k = 0; k < 4; k++) {
                adj gg = hit(maze, cur.x, k);
                if (done[gg.to.i][gg.to.j])
                    continue;
                pq.push({gg.to, cur.culdist + gg.len});
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
int main() {
    Solution s;
    int ans = s.shortestDistance({{0, 0, 1, 0, 0},
                                  {0, 0, 0, 0, 0},
                                  {0, 0, 0, 1, 0},
                                  {1, 1, 0, 1, 1},
                                  {0, 0, 0, 0, 0}},
                                 {0, 4}, {4, 4});
    cout << ans << endl;
}
