// cesun, 9/27/20 9:09 PM.
#include <algorithm>
#include <cstdio>

template<int D0, int D1>
void print_2darr(const int (&arr)[D0][D1]) {
    static char buf[25600];
    char *cur = buf;
    cur += sprintf(cur, "idx:");
    for (int i = 0; i < D1; ++i) {
        cur += sprintf(cur, "%4d", i);
    }
    puts(buf);
    for (int i = 0; i < D0; ++i) {
        cur = buf;
        cur += sprintf(cur, "%2d: ", i);
        for (const int e : arr[i]) {
            cur += sprintf(cur, "%4d", e);
        }
        puts(buf);
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

//closest_subset_sum_proto0<3, 14>({7, 10, 4})
//idx:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
// 0:    0   0   0   0   0   0   0   7   7   7   7   7   7   7   7
// 1:    0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
// 2:    0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
//
//idx:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
// 0:    0   0   0   0   0   0   0   7   7   7   7   7   7   7   7
// 1:    0   0   0   0   0   0   0   7   7   7  10  10  10  10  10
// 2:    0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
//
//idx:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
// 0:    0   0   0   0   0   0   0   7   7   7   7   7   7   7   7
// 1:    0   0   0   0   0   0   0   7   7   7  10  10  10  10  10
// 2:    0   0   0   0   4   4   4   7   7   7  10  11  11  11  14
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

// An improved implementation. We eliminate that condition check by directly start j from arr[i].
// Now the content of `dp[][]` does not strictly follow its definition anymore. Notice how `dp[1][7-9]`
// is 0. Apparently this is not the case, since as demonstrated above, knapsacks of capacity 7 to 9 can
// for sure contain that integer 7. Let's prove this is still a correct algorithm.

//closest_subset_sum_proto1<3, 14>({7, 10, 4})
//idx:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
// 0:    0   0   0   0   0   0   0   7   7   7   7   7   7   7   7
// 1:    0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
// 2:    0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
//
//idx:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
// 0:    0   0   0   0   0   0   0   7   7   7   7   7   7   7   7
// 1:    0   0   0   0   0   0   0   0   0   0  10  10  10  10  10
// 2:    0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
//
//idx:   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
// 0:    0   0   0   0   0   0   0   7   7   7   7   7   7   7   7
// 1:    0   0   0   0   0   0   0   0   0   0  10  10  10  10  10
// 2:    0   0   0   0   4   4   4   4   4   4  10  10  10  10  14
template<int K, int MAXN>
int closest_subset_sum_proto1(const int (&arr)[K]) {
    // dp[i][j]: when only the first i integers are considered, the max weight attainable for the knapsack of size j
    // the answer is dp[K-1][MAXN] so you want the second dimension to have size MAXN+1
    static int dp[K][MAXN + 1];
    // initialize dp[0][]
    for (int j = arr[0]; j <= MAXN; ++j) {
        dp[0][j] = arr[0];
    }
    // dp[0][]: 0,0,0,0,....,0, arr[0], arr[0], ..., arr[0].
    print_2darr(dp);
    for (int i = 1; i < K; ++i) {
        for (int j = arr[i]; j <= MAXN; ++j) {
            dp[i][j] = std::max(dp[i - 1][j], arr[i] + dp[i - 1][j - arr[i]]);
        }
        print_2darr(dp);
    }
    return dp[K - 1][MAXN];
}


int main() {
    puts("closest_subset_sum_proto0<3, 14>({7, 10, 4})");
    printf("ans=%d\n", closest_subset_sum_proto0<3, 14>({7, 10, 4}));

//    puts("closest_subset_sum_proto1<3, 14>({7, 10, 5})");
//    printf("ans=%d\n", closest_subset_sum_proto1<3, 14>({7, 10, 5}));
}
