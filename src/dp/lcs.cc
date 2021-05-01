// longest common subsequence

#include <bits/stdc++.h>

using namespace std;

int lcs_length_prototype(const string &a, const string &b) {
    // dp[i][j]: length of lcs if only considering a[0,i-1] and b[0,j-1]
    // We init all cell to 0 for now, but actually we only need to first row and first column to be 0
    vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, 0));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            if (a[i] == b[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }
    return dp[a.size()][b.size()];
}

// If we need to reconstruct the lcs, this space optimization can't be used.
constexpr int MAX_B_SZ = 1000;
static int dp[2][MAX_B_SZ + 1];

int lcs_length_optimized(const string &a, const string &b) {
    memset(dp, 0, sizeof dp); // memset(dp[1],0,sizeof dp[1]) is enough
    int curi, previ;
    for (int i = 0; i < a.size(); i++) {
        curi = i & 1, previ = curi ^ 1;
        for (int j = 0; j < b.size(); j++) {
            if (a[i] == b[j]) {
                dp[curi][j + 1] = dp[previ][j] + 1;
            } else {
                dp[curi][j + 1] = max(dp[previ][j + 1], dp[curi][j]);
            }
        }
    }
    return dp[curi][b.size()];
}