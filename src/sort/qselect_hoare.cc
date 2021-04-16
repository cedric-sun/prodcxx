#include <bits/stdc++.h>
using namespace std;

// find the largest k elements; result in a[n-k ~ k-1] (unsorted),
// and a[n-k] being exactly the k-th largest element
// [l,r]
void quick_select(vector<int> &a, int l, int r, int k) {
    if (l < r) {
        int gauge = a[(l + r) >> 1];
        int i = l - 1, j = r + 1;
        while (true) {
            do {
                ++i;
            } while (a[i] < gauge);
            do {
                --j;
            } while (a[j] > gauge);
            if (i >= j)
                break;
            swap(a[i], a[j]);
        }
        if (a.size() - j - 1 < k)
            quick_select(a, l, j, k);
        else
            quick_select(a, j + 1, r, k);
    }
}

// lc215
class Solution {
public:
    int findKthLargest(vector<int> &nums, int k) {
        quick_select(nums, 0, nums.size() - 1, k);
        return nums[nums.size() - k];
    }
};
