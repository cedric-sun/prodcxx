/**
 * LIS O(n^2) Solution.
 *
 * We are interesting in this version because it represents a general dp
 * technique that can solve problems O(n logn) version can't solve.
 *
 * The dp[] array, instead of storing the length of LIS that ends at a[i] (which
 * is init-ed to 1 and potentially increase by 1 each time we inspect a new
 * element), can represent "weight" as well.
 */

#include <bits/stdc++.h>
using namespace std;

int lis_length(vector<int> &a) {
    // dp[i]: length of the LIS that ends at a[i]; init to 1
    vector<int> dp(a.size(), 1);
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[i] > a[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        // dp[i] settled permanently
    }
    int ans = 0;
    for (int i = 0; i < a.size(); ++i) {
        ans = max(ans, dp[i]);
    }
    return ans;
}

// lc 354
class Solution {
public:
    int maxEnvelopes(vector<vector<int>> &envs) {
        sort(envs.begin(), envs.end(), [](const auto &a, const auto &b) {
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });
        vector<int> second_dim;
        second_dim.reserve(envs.size());
        for (const auto &e : envs)
            second_dim.push_back(e[1]);
        return lis_length(second_dim);
    }
};
