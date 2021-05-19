// cesun, 9/19/20 9:30 PM.

/*
 * When input sequence is of type int and does not touch INT_MAX,
 * lis can be further boosted by directly storing the value of the tail of lis
 * in array d[].
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // nums[i] <= 10^4
    int lengthOfLIS(vector<int> &nums) {
        // n+1 ensures at least 1 INT_MAX in the tail
        vector<int> d(nums.size() + 1, INT_MAX);
        for (int x : nums)
            *lower_bound(d.begin(), d.end(), x) = x;
        int ans = 0;
        while (d[ans] != INT_MAX)
            ans++;
        return ans;
    }
};
