#include <bits/stdc++.h>

using namespace std;

// Given an integer array, find the max subarray sum.
// This is trivial when all elements are positive, i.e. answer is summing up the whole array
// Things get interesting when the array contains negative value, e.g. [5,4,-1,7,8].
// We are willing to take the punishment caused by putting -1 into the sum,
// because this allows us to make a longer subarray with larger sum.
// But when the negative value is too large, e.g. [5,4,-90,7,8], we need to be smart enough to not include -90.

int max_subarray_sum_prototype(vector<int> &a) {
    vector<int> dp(a.size()); // dp[i]: the max sum of subarray that end exactly at a[i] (must include a[i])
    dp[0] = a[0];
    for (int i = 1; i < a.size(); i++) {
        dp[i] = max(dp[i - 1] + x[i], x[i]);
    }
    // and among subarrays with max sum that end exactly at each position, we find the max
    int ans = INT_MIN;
    for (int value : dp)
        ans = max(ans, value);
    return ans;
}

// We make 2 observations here:
// 1. dp[i] only depends on dp[i-1] and x[i]
// 2. Once dp[i] is computed, it never change.
// These allows us to use only O(1) space, and do everything in 1 pass.
int max_subarray_sum_optimized(vector<int> &a) {
    int dp = 0, ans = INT_MIN; // mind arithmetic overflow though
    for (int value : a) {
        dp = max(dp + a, a);
        ans = max(ans, dp);
    }
    return ans;
}