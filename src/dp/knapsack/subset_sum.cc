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
}

int main() {
    vector<int> data = {7, 10, 5};
    int cap = 14;
    cout << subset_sum_01_closest(data, cap) << endl;
    cout << recursive::subset_sum_recursive(data, cap) << endl;
}
