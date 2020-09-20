// cesun, 9/10/20 11:34 PM.

#include <vector>

#include "../ds/disjoint-set.cc"

// unit test: http://acm.hdu.edu.cn/showproblem.php?pid=1233

#include "../util.cc"

#include <cstdint>
#include <queue>

struct edge {
    int i, j;
    int_fast64_t len;

    bool inline operator<(const edge &o) const {
        return len > o.len;
    }
};

#include <cstdio>
int main() {
    fast_io();
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        const int m = n * (n - 1) >> 1;
        vector<edge> es{static_cast<unsigned long>(m)};
        for (int i = 0; i < m; ++i) {
            scanf("%d %d %ld", &es[i].i, &es[i].j, &es[i].len);
        }
        std::priority_queue<edge> pq{std::make_move_iterator(es.begin()),
                                     std::make_move_iterator(es.end())};
        disjoint_set ds{n + 1};
        int e_cnt = 0;
        int_fast64_t ans = 0;
        while (!pq.empty()) {
            const edge &e = pq.top();
            // i leader, j leader
            const int il = ds.find(e.i), jl = ds.find(e.j);
            if (il != jl) {
                ds.join_leader(il, jl);
                e_cnt++;
                ans += e.len;
                if (e_cnt >= n - 1)
                    break;
            }
            pq.pop();
        }
        printf("%ld\n", ans);
    }
}
