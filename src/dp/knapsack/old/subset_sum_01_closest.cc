// Sun Sep 27 12:12:53 AM EDT 2020

/*
 * Given K integers, compute the sum of the subset that has
 * the greatest sum <= N
 */

#include <algorithm>
#include <cstring>

#define MAX_ITEM_N 1005
#define MAX_CAP 1005

static int item_n, capacity;
static int dp[MAX_CAP + 1], lb[MAX_ITEM_N], items[MAX_ITEM_N];

int knapsack() {
    memset(dp, 0, (capacity + 1) * sizeof(*dp)); // capacity+1 is crucial
    lb[item_n - 1] = capacity;
    for (int i = item_n - 2; i >= 0; --i)
        lb[i] = lb[i + 1] - items[i + 1];
    for (int i = 0; i < item_n; ++i) {
        const int &x = items[i];
        const int lbi = std::max(lb[i], x);
        if (capacity >= x) {
            dp[capacity] = std::max(dp[capacity], x + dp[capacity - x]);
            if (dp[capacity] == capacity) return capacity; // a further optimization but only work for subset sum knapsack
        }
        for (int j = capacity - 1; j >= lbi; --j) {
            dp[j] = std::max(dp[j], x + dp[j - x]);
        }
    }
    return dp[capacity];
}
