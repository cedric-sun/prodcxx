#include <bits/stdc++.h>

using namespace std;

void print_dp(const vector<vector<int>> &dp, const vector<int> &cost,
              const vector<int> &value) {
    fputs("idx: ", stdout);
    for (int i = 0; i < dp[0].size(); ++i) {
        printf("%12d", i);
    }
    putchar('\n');
    fputs("(-,-)", stdout);
    for (int j = 0; j < dp[0].size(); j++)
        printf("%12d", dp[0][j]);
    putchar('\n');
    for (int i = 0; i < cost.size(); ++i) {
        printf("(%d,%d)", cost[i], value[i]);
        for (int j = 0; j < dp[0].size(); ++j) {
            printf("%12d", dp[i + 1][j]);
        }
        putchar('\n');
    }
    puts("--------------------");
}

namespace knapsack_01_max_value {
int prototype(const vector<int> &costs, const vector<int> &values,
              const int cap) {
    const int n = costs.size(); // # of items
    vector<vector<int>> dp(n + 1, vector<int>(cap + 1, 0));
    for (int i = 0; i < n; i++) {
        print_dp(dp, costs, values);
        for (int j = costs[i]; j <= cap; j++) {
            dp[i + 1][j] = max(dp[i][j], dp[i][j - costs[i]] + values[i]);
        }
    }
    print_dp(dp, costs, values);
    return dp[n][cap];
}
} // namespace knapsack_01_max_value

namespace knapsack_01_exact_fill {
int prototype(const vector<int> &costs, const vector<int> &values,
              const int cap) {
    const int n = costs.size(); // # of items
    vector<vector<int>> dp(n + 1, vector<int>(cap + 1, INT_MIN));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        print_dp(dp, costs, values);
        for (int j = costs[i]; j <= cap; j++) {
            dp[i + 1][j] = max(dp[i][j], dp[i][j - costs[i]] + values[i]);
        }
    }
    print_dp(dp, costs, values);
    return dp[n][cap];
}
} // namespace knapsack_01_exact_fill

namespace knapsack_unbounded_min_item_instance_count_when_exact_fill {
// lc322 coin change

// unbounded knapsack with only given cost for each item,
// find the min item instance count when given capacity is exactly filled.
// Alternatively, can be though of an unbounded knapsack with given cost and
// constant value 1 each item, find the min value when cap is exactly filled.
static int dp[10000 + 1];

class Solution {
public:
    int coinChange(const vector<int> &coins, int amount) {
        constexpr int BAD_APPLE = 0xaeaeaeae;
        memset(dp, 0xae, sizeof dp);
        dp[0] = 0;
        for (int c : coins) {
            for (int j = c; j <= amount; j++) {
                if (dp[j] != BAD_APPLE && dp[j - c] != BAD_APPLE) {
                    dp[j] = min(dp[j], dp[j - c] + 1);
                } else if (dp[j - c] != BAD_APPLE) {
                    dp[j] = dp[j - c] + 1;
                }
            }
        }
        if (dp[amount] == BAD_APPLE)
            return -1;
        return dp[amount];
    }
};
} // namespace knapsack_unbounded_min_item_instance_count_when_exact_fill

namespace knapsack_unbounded_exact_fill_plan_count {
// For each item we only have a cost,
// Find the # of plan to fill given capacity exactly.
// A plan is defined as a **combination** of instances of items,
// i.e To reach capacity 3, 1+2 and 2+1 are the same plan.

// Knapsack is going wild sometimes, since we don't even have the concept of
// value properly defined.

// lc 518
// Without considering any coins, we naturally reach cap 0, i.e. dp[0] = 1
// This is also required in order to get a consistent state definition
// and state transfer rule
int dp[5001];

class Solution {
public:
    int change(int amount, vector<int> &coins) {
        constexpr int UNATT = 0x80808080;
        memset(dp, UNATT, sizeof dp);
        dp[0] = 1;
        for (int c : coins) {
            for (int j = c; j <= amount; j++) {
                if (dp[j - c] != UNATT && dp[j] != UNATT) {
                    dp[j] += dp[j - c];
                } else if (dp[j - c] != UNATT) {
                    dp[j] = dp[j - c];
                }
            }
        }
        if (dp[amount] == UNATT)
            return 0;
        return dp[amount];
    }
};

} // namespace knapsack_unbounded_exact_fill_plan_count

namespace knapsack_01_2d_inexact_max {
// lc474
// 2d cost 0-1 knapsack with constant value 1, find max value sum inexact fill
// # of items in [1,100]; cap0, cap1 in [1,100]
//
// About order of iteration for 2d 0-1 knapsack.
// 8 variants exist by combining
// 1. i (cost on cap0) ascending/descending
// 2. j (cost on cap1) ascending/descending
// 3. nested loop order: i contains j / j contains i
//
// Among them, the 4 outer loop decreasing ones are safe, i.e.
// 1. i and j both decreasing is always safe, and inner/outer loop can exchange.
// 2. i contains j and i decreasing is safe
// 3. j contains i and j decreasing is safe
//
// We choose the both decreasing one.

int dp[101][101];

struct item_t {
    int c0, c1;
};

int knapsack_01_2d_inexact_max(const vector<item_t> &items, const int cap0,
                               const int cap1) {
    memset(dp, 0, sizeof dp);
    for (const item_t &item : items) {
        for (int i = cap0; i >= item.c0; --i) {
            for (int j = cap1; j >= item.c1; --j) {
                dp[i][j] = max(dp[i][j], dp[i - item.c0][j - item.c1] + 1);
            }
        }
    }
    return dp[cap0][cap1];
}
class Solution {
public:
    int findMaxForm(const vector<string> &strs, int cap0, int cap1) {
        vector<item_t> items;
        for (const auto &s : strs) {
            const int zcnt = count(s.cbegin(), s.cend(), '0');
            items.push_back({zcnt, static_cast<int>(s.size() - zcnt)});
        }
        return knapsack_01_2d_inexact_max(items, cap0, cap1);
    }
};

} // namespace knapsack_01_2d_inexact_max

int main() {
    // knapsack_01_max_value::prototype({2, 4, 5}, {3, 3, 7}, 14);
    knapsack_01_exact_fill::prototype({2, 4, 5}, {3, 3, 7}, 14);
}
