// cesun, 9/27/20 9:09 PM.
#include <algorithm>
#include <cstdio>

static char buf[25600];

template<int D>
void print_arr(const int idx, const int (&arr)[D]) {
    char *cur = buf;
    cur += sprintf(cur, "%2d: ", idx);
    for (const int e : arr) {
        cur += sprintf(cur, "%4d", e);
    }
    puts(buf);
}

void print_header(const int n) {
    char *cur = buf;
    cur += sprintf(cur, "idx:");
    for (int i = 0; i < n; ++i) {
        cur += sprintf(cur, "%4d", i);
    }
    puts(buf);
}

template<int D0, int D1>
void print_2darr(const int (&arr)[D0][D1]) {
    print_header(D1);
    for (int i = 0; i < D0; ++i) {
        print_arr(i, arr[i]);
    }
    putchar('\n');
}

/*
 *  Closest Subset Sum Problem.
 *  Given K positive integers, compute the subset that has the greatest sum <= N.
 */

// dp[i][j]: For all the "take" or "not take" combinations of the first i items, the max payload attainable within the knapsack of capacity j.

// let x_i denote all possible {0,1}^i, let f(x) be the sum of the subset of item picked using x as a bitmask.
// dp[i][j] <=> maximize f(x_i) subject to f(x_i) <= j (over all possible x_i)
// maximize f(x_i) subject to f(x_i) <= j
// = max( maximize f(0 + x_{i-1}) subject to f(x_{i-1}) <= j        (over all possible x_{i-1}),
//        maximize f(1 + x_{i-1}) subject to f(x_{i-1}) <= j-w[i]   (over all possible x_{i-1})
//      )

// For the first case there could be multiple x_{i-1} making f(x_{i-1}) <= j true; I guess this is where my weird intuition
// of "if we don't take the i-th item, dp[i][j] can't be simply dp[i-1][j] but is the maximum of dp[i-1][0 ~ j]" comes from.
// But also notice that f(x_{i-1}) === f(0 + x_{i-1}) which is the thing we are maximizing. So among those
// x_{i-1} making f(x_{i-1}) <= j true, we want the largest f(x_{i-1}) <= j, which is the definition of dp[i-1][j]. So it's
// enough to just check dp[i-1][j].

// The most straight forward implementation.
// The content of `dp[][]` strictly follows its definition.
// Note how dp[1][7-9] and dp[2][7-9] is 7, meaning that
// - Consider only the first 2 integer, for knapsacks of capacity 7 to 9, the max payload is 7 (attained by put that 7 into knapsack)
// - Consider only the first 3 integer, for knapsacks of capacity 7 to 9, the max payload is 7 (same)

template<int K, int MAXN>
int closest_subset_sum_proto0(const int (&arr)[K]) {
    // the answer is dp[K-1][MAXN] so you want the second dimension to have size MAXN+1
    static int dp[K][MAXN + 1];
    // initialize dp[0][]
    for (int j = arr[0]; j <= MAXN; ++j) {
        dp[0][j] = arr[0];
    }
    // dp[0][]: 0,0,0,0,....,0, arr[0], arr[0], ..., arr[0].
    print_2darr(dp);
    for (int i = 1; i < K; ++i) {
        for (int j = 0; j <= MAXN; ++j) {
            if (j < arr[i])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = std::max(dp[i - 1][j], arr[i] + dp[i - 1][j - arr[i]]);
        }
        print_2darr(dp);
    }
    return dp[K - 1][MAXN];
}

// An BUGGY implementation: https://github.com/tianyicui/pack/issues/4
template<int K, int MAXN>
int BUG_closest_subset_sum_proto1(const int (&arr)[K]) {
    // the answer is dp[K-1][MAXN] so you want the second dimension to have size MAXN+1
    static int dp[K][MAXN + 1];
    // initialize dp[0][]
    for (int j = arr[0]; j <= MAXN; ++j) {
        dp[0][j] = arr[0];
    }
    // dp[0][]: 0,0,0,0,....,0, arr[0], arr[0], ..., arr[0].
    print_2darr(dp);
    for (int i = 1; i < K; ++i) {
        for (int j = arr[i]; j <= MAXN; ++j) { // ignoring j<arr[i] incurring terrible bug.
            dp[i][j] = std::max(dp[i - 1][j], arr[i] + dp[i - 1][j - arr[i]]);
        }
        print_2darr(dp);
    }
    return dp[K - 1][MAXN];
}

// A space optimization and everything sweetly work together:
// 1. the initialization step is naturally combined into the major loop
// 2. The attempt to eliminate the `j < arr[i]` check in the previous buggy implementation
//      incurs bug, since we always need to copy dp[i - 1][j] to dp[i][j] when `j < arr[i]`.
//      But with the space optimization, we are now working on the same array, and due to
//      the order of iteration, what we need to copy previously now just naturally sit in their place.
template<int K, int MAXN>
int closest_subset_sum(const int (&arr)[K]) {
    // the answer is dp[K-1][MAXN] so you want the second dimension to have size MAXN+1
    static int dp[MAXN + 1];
    print_header(MAXN + 1);
    int i = 0;
    for (int x : arr) {
        for (int j = MAXN; j >= x; --j) {
            dp[j] = std::max(dp[j], x + dp[j - x]);
        }
        print_arr(i++, dp);
    }
    return dp[MAXN];
}

// A constant factor optimization by only compute the necessary triangle on the 2D array
template<int K, int MAXN>
int closest_subset_sum_opt(const int (&arr)[K]) {
    // the answer is dp[K-1][MAXN] so you want the second dimension to have size MAXN+1
    static int dp[MAXN + 1]; // 0 init required if this function is called more than once.
    // precompute lb[i]= MAXN- \sum_{i+1}^{N}
    static int lb[K];
    lb[K - 1] = MAXN;
    for (int i = K - 2; i >= 0; --i) {
        lb[i] = lb[i + 1] - arr[i + 1];
    }
    print_header(MAXN + 1);
    for (int i = 0; i < K; ++i) {
        const int &x = arr[i];
        const int lbi = std::max(lb[i], x);
        for (int j = MAXN; j >= lbi; --j) {
            dp[j] = std::max(dp[j], x + dp[j - x]);
        }
        print_arr(i, dp);
    }
    return dp[MAXN];
}

namespace unbounded_subset_sum {
    template<int K, int MAXN>
    int work(const int (&arr)[K]) {
        static int dp[K][MAXN + 1];
        // memset dp to 0 if invoked multiple times ...
        // there is no lb[] optimization now since dp[K - 1][MAXN] now depends on the whole 2d array
        int (&dp0)[MAXN + 1] = dp[0];
        for (int j = arr[0]; j <= MAXN; ++j) {
            dp0[j] = dp0[j - arr[0]] + arr[0];
        }
        print_2darr(dp);
        for (int i = 1; i < K; ++i) {
            for (int j = arr[i]; j <= MAXN; ++j) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - arr[i]] + arr[i]);
            }
            print_2darr(dp);
        }
        return dp[K - 1][MAXN];
    }

    template<int K, int MAXN>
    int improve0(const int (&arr)[K]) {
        static int dp[MAXN + 1];
        // memset dp to 0 if invoked multiple times ...
        // there is no lb[] optimization now since dp[K - 1][MAXN] now depends on the whole 2d array
        print_header(MAXN + 1);
        for (int i = 0; i < K; ++i) {
            for (int j = arr[i]; j <= MAXN; ++j) {
                dp[j] = std::max(dp[j], dp[j - arr[i]] + arr[i]);
            }
            print_arr(i, dp);
        }
        return dp[MAXN];
    }
}

int main() {
//    puts("-----------------------------------------");
    printf("ans=%d\n", closest_subset_sum_proto0<3, 14>({7, 10, 5}));
//    printf("ans=%d\n", BUG_closest_subset_sum_proto1<3, 14>({7, 10, 5}));
//    puts("-----------------------------------------");
    printf("ans=%d\n", closest_subset_sum<3, 14>({7, 10, 5}));
//    puts("-----------------------------------------");
//    printf("ans=%d\n", closest_subset_sum_opt<3, 14>({7, 10, 5}));
//    printf("ans=%d\n", unbounded_subset_sum::work<3, 14>({7, 10, 5}));
    printf("ans=%d\n", unbounded_subset_sum::improve0<3, 14>({7, 10, 5}));
}
