// cesun, 9/20/20 1:24 PM.

/*
 * next_permutation implementation from c++ std library
 * reason not to use binary search: https://stackoverflow.com/a/17212740/8311608
 *
 *      i   i1          i2
 * 10   5   9   8   7   6   4   3   2   1
 */

#include <algorithm>

// precondition: n>=2
template<typename T>
bool next_permu(T *const a, const int n) {
    int i = n - 1;
    while (true) {
        int i1, i2;
        i1 = i;
        // scan from tail, find the first a[i]<a[i1] : i1-i=1
        if (a[--i] < a[i1]) {
            i2 = n;
            // scan from tail, find the first a[i2]>a[i] (i.e. i2>=i1)
            while (!(a[i] < a[--i2]));
            std::swap(a[i], a[i2]);
            std::reverse(a + i1, a + n); // the costly part
            return true;
        }
        // if the whole array is entirely non-ascending
        if (i == 0) {
            std::reverse(a, a + n); // the costly part
            return false;
        }
    }
}

//test: https://leetcode.com/problems/next-permutation/

#include <vector>
using std::vector;
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size()>=2)
            next_permu(nums.data(), nums.size());
    }
};
