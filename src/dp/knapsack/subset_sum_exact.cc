// cesun, 9/27/20 2:26 AM.

/*
 * Given K integers, is there a subset whose sum is exactly N?
 */

#include <algorithm>
#include <cstring>

#define MAX_ITEM_N 1005
#define MAX_CAP 1005

static int item_n, capacity;
static int lb[MAX_ITEM_N], items[MAX_ITEM_N];
static bool dp[MAX_CAP + 1];

bool knapsack() {
    memset(dp, 0, (capacity + 1) * sizeof(*dp)); // capacity+1 is crucial
    dp[0] = true;
    lb[item_n - 1] = capacity;
    for (int i = item_n - 2; i >= 0; --i)
        lb[i] = lb[i + 1] - items[i + 1];
    for (int i = 0; i < item_n; ++i) {
        const int &x = items[i];
        const int lbi = std::max(lb[i], x);
        if (capacity >= x && dp[capacity - x]) return true;
        for (int j = capacity - 1; j >= lbi; --j) {
            if (dp[j - x]) dp[j] = true;
        }
    }
    return false;
}
