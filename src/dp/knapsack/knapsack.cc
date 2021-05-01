#include <bits/stdc++.h>

using namespace std;

void print_dp(const vector<vector<int>> &dp, const vector<int> &cost, const vector<int> &value) {
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
    int prototype(const vector<int> &costs, const vector<int> &values, const int cap) {
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
}

namespace knapsack_01_exact_fill {
    int prototype(const vector<int> &costs, const vector<int> &values, const int cap) {
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
}

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
}

namespace knapsack_unbounded_exact_fill_plan_count {
    // For each item we only have a cost,
    // Find the # of plan to fill given capacity exactly.
    // A plan is defined as a **combination** of instances of items,
    // i.e To reach capacity 3, 1+2 and 2+1 are the same plan.

    // Knapsack is going wild sometimes, since we don't even have the concept of value properly defined.

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

}

int main() {
    //knapsack_01_max_value::prototype({2, 4, 5}, {3, 3, 7}, 14);
    knapsack_01_exact_fill::prototype({2, 4, 5}, {3, 3, 7}, 14);
}