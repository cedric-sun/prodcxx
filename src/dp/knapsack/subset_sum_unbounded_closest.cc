// cesun, 9/29/20 11:24 PM.

#include <algorithm>
#include <cstring>

#define MAX_ITEM_N 1005
#define MAX_CAP 1005

static int item_n, capacity;
static int dp[MAX_CAP + 1], items[MAX_ITEM_N];

int unbounded_knapsack() {
    memset(dp, 0, (capacity + 1) * sizeof(*dp)); // capacity+1 is crucial
    for (int i = 0; i < item_n; ++i) {
        const int &x = items[i];
        for (int j = x; j <= capacity; ++j) {
            dp[j] = std::max(dp[j], x + dp[j - x]);
        }
        if (dp[capacity] == capacity) return capacity; // a further optimization but only work for subset sum knapsack
    }
    return dp[capacity];
}
