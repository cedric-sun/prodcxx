// Sun Sep 27 12:12:53 AM EDT 2020

/*
 * Given K integers, compute the subset that has the greatest sum <= N
 */

#include <algorithm>

#define K 42
#define MAXN int(1e9)

// dp[j]: when only the first i integers are considered,
// the max weight attainable for the knapsack of size j,
// where i is implicit (the index of the outer loop)
static int dp[MAXN];

int work(int (&arr)[K]) {
    // dp[] .bss section is 0-filled by dynamic loader
    for (int i = 0; i < K; ++i) {
        for (int j = MAXN; j >= arr[i]; --j) {
            dp[j] = std::max(dp[j], arr[i] + dp[j - arr[i]]);
        }
    }
}
