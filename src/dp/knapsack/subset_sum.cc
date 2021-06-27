// subset sum problem is knapsack but weight is always quantitatively identical
// to cost for each item; This type of specialization of knapsack exhibits some
// interesting properties.

#include <bits/stdc++.h>

using namespace std;

int subset_sum_01_closest(const vector<int> &items, const int cap) {
    vector<int> dp(cap + 1); // init to 0
    for (int value : items) {
        for (int j = cap; j >= value; --j) {
            dp[j] = max(dp[j], value + dp[j - value]);
        }
    }
    return dp.back();
}

int subset_sum_01_closest_triangle_opt(const vector<int> &items,
                                       const int cap) {
    vector<int> dp(cap + 1), lb(items.size());
    lb.back() = cap;
    for (int i = items.size() - 2; i >= 0; --i)
        lb[i] = lb[i + 1] - items[i + 1];
    for (int i = 0; i < items.size(); ++i) {
        const int value = items[i], lbi = max(lb[i], value);
        for (int j = cap; j >= lbi; --j) {
            dp[j] = max(dp[j], value + dp[j - value]);
        }
    }
    return dp.back();
}

namespace recursive {
// the recursive implementation accesses even fewer states
// comparing to the triangle optimization of the iterative one.
int ss_crazy(const vector<int> &items, vector<vector<int>> &dp, int i, int j) {
    if (i == -1) {
        return 0;
    }
    if (dp[i][j] != -1)
        return dp[i][j];
    int dpij = ss_crazy(items, dp, i - 1, j);
    if (j >= items[i])
        dpij = max(dpij, ss_crazy(items, dp, i - 1, j - items[i]) + items[i]);
    return dp[i][j] = dpij;
}

int subset_sum_recursive(const vector<int> &items, int cap) {
    vector<vector<int>> dp(items.size(), vector<int>(cap + 1, -1));
    return ss_crazy(items, dp, items.size() - 1, cap);
}
} // namespace recursive

// Rationale: for bitset c[0] = true; for each value in items, we keep c |=
// (c<<n); crop the bitset to the least significant bits [cap,0], find the most
// significant 1 (can be done using CLZ instruction or alike; GCC bulit-in:
// https://stackoverflow.com/a/673781/8311608
int subset_sum_01_closest_crazier_bitmagic(const vector<int> &items, int cap) {
    // TODO: CLZ on std::bitset
}

bool exact_subset_sum_01_attainability(const vector<int> &items,
                                       const int target) {
    // max possible sum of all items, since we will be left shifting the first
    // bit sum(items) times
    constexpr int MAXN = 20010;
    auto c = bitset<MAXN>();
    c[0] = true;
    for (auto n : items) {
        c |= (c << n);
        if (c[target])
            return true;
    }
    return false;
}

namespace subset_sum_01_inexact_max_bool {
// an interesting implementation that find 01-subset sum inexact max fill, but
// only use a visited[] bool array.
//
// Feels like the done[] version of dijkstra.
int work(const vector<int> &items, const int cap) {
    vector<bool> dp(cap + 1, false);
    dp[0] = true;
    int ans = 0;
    for (int item : items) {
        for (int j = cap; j >= item; j--) {
            if (dp[j - item]) {
                dp[j] = true;
                ans = max(ans, j);
            }
        }
    }
}
} // namespace subset_sum_01_inexact_max_bool

int main() {
    vector<int> data = {7, 10, 5};
    int cap = 14;
    cout << subset_sum_01_closest(data, cap) << endl;
    cout << recursive::subset_sum_recursive(data, cap) << endl;
}
