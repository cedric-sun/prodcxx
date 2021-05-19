// lc152
#include <bits/stdc++.h>
using namespace std;

// dpmax[i]: max subarray product that ends exactly at a[i]
// dpmin[i]: min subarray product that ends exactly at a[i]
int dpmax[20000], dpmin[20000];

class Solution {
public:
    int maxProduct(vector<int> &a) {
        dpmax[0] = dpmin[0] = a[0];
        for (int i = 1; i < a.size(); ++i) {
            // by knowing dpmin[], we keep the hope that when a very negative
            // subarray product ends at the previous position, and the current
            // element is also negative, we know it's time to
            // make a negative-negative-positive flip, and potentially have
            // a larger subarray product.
            dpmax[i] = max({a[i], dpmax[i - 1] * a[i], dpmin[i - 1] * a[i]});
            dpmin[i] = min({a[i], dpmax[i - 1] * a[i], dpmin[i - 1] * a[i]});
        }
        int ans = INT_MIN;
        for (int i = 0; i < a.size(); ++i) {
            ans = max(ans, dpmax[i]);
        }
        return ans;
    }
};

