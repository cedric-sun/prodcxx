// cesun, 9/7/20 1:07 AM.

#include <algorithm>

struct rmq_sparse_table {
#define K 25 // K should be floor(log2(n))
    int (*st)[K + 1];
    int *FLOOR_LOG2;

    rmq_sparse_table(const int *const arr, const int n) {
        st = new int[n][K + 1];
        for (int i = 0; i < n; i++)
            st[i][0] = arr[i];

        for (int j = 1; j <= K; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        FLOOR_LOG2 = new int[n + 1];
        FLOOR_LOG2[1] = 0;
        for (int i = 2; i <= n; i++)
            FLOOR_LOG2[i] = FLOOR_LOG2[i >> 1] + 1;
    }

    int query(const int l, const int r) {
        const int j = FLOOR_LOG2[r - l + 1];
        return std::min(st[l][j], st[r - (1 << j) + 1][j]);
    }

    virtual ~rmq_sparse_table() {
        delete[] st;
        delete[] FLOOR_LOG2;
    }
};


//unit test https://www.spoj.com/problems/RMQSQ/
#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
    }
    rmq_sparse_table x{arr, n};
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", x.query(l, r));
    }
}