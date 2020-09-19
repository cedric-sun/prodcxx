// cesun, 9/13/20 2:44 AM.

#include <cstring>
#include <algorithm>

#define MAXN 10005

template<typename T>
struct slis {

    // [0,r)
    static inline int lower_bound(const T *const a, const int *const d, int r, const T &key) {
        int l = 0;
        while (l < r) {
            int m = (l + r) >> 1; // or l+((n-l)>>1)
            if (a[d[m]] < key) l = m + 1;
            else r = m;
        }
        return l;
    }

    //precond: n>0
    static int work(const T *const a, const int n) {
        int *d = new int[n]; // a[d[i]] is the value of tail of lis of size i+1
        d[0] = 0; // init: lis of size 1 end at a[0]
        int dsz = 1;
        for (int i = 1; i < n; ++i) {
            if (a[i] <= a[d[0]])
                d[0] = i;
            else if (a[i] > a[d[dsz - 1]])
                d[dsz++] = i;
            else if (a[i] == a[d[dsz - 1]])
                d[dsz - 1] = i;
            else
                d[lower_bound(a, d, dsz, a[i])] = i;
            // or simplified version:
//            int j = lower_bound(a, d, dsz, a[i]);
//            if (j == dsz) dsz++;
//            d[j] = i;
        }
        int ans = d[dsz - 1];
        delete[] d;
        return ans;
    }
};

struct Envelope {
    int w, h;

    bool operator<(const Envelope &rhs) const {
        return w < rhs.w && h < rhs.h;
    }

    bool operator<=(const Envelope &rhs) const {
        return w < rhs.w && h < rhs.h;
    }

    bool operator>(const Envelope &rhs) const {
        return w < rhs.w && h < rhs.h;
    }

    bool operator>=(const Envelope &rhs) const {
        return w < rhs.w && h < rhs.h;
    }
};

int main() {
    Envelope xx[300];
    int ans = slis<Envelope>::work(xx, 300);
}

namespace lis {
    static long d[MAXN]; // d[i]: value of tail of lis of size (i+1)
    // d is always sorted, this is because:
    // 1. if there are multiple lis of length t, the updating policy guarantees d[t] is the value of smallest tail
    // 2. Assume p>q but d[p] < d[q], in that implicit lis of size p, there must contain a lis of size q whose tail is smaller than
    //      d[q] (since lis is ascending). But by our updating policy, this couldn't happened.

    static const int *a;

    template<typename T>
    static int lis(const int *const _a, const int n) {
        a = _a;
        memset(d, 0x1f, n * sizeof(*d)); // some gigantic value that int cannot reach
        const long guard = d[0];
        for (int i = 0; i < n; ++i) {
            *std::lower_bound(d, d + n, a[i]) = a[i];
            // all the benefits of not worrying about duplicate d element and keep elems in d as small as possible
            // comes from lower_bound ...
            // DO NOT USE UPPER BOUND! UPPER BOUND + SAFE CHECK IS SILLY!
        }
        int ans = 0;
        while (d[ans++] != guard);
        return ans;
    }
}

namespace lis_bt {

}

namespace lnds { // longest non-decreasing subsequence

}


// test: https://leetcode.com/problems/longest-increasing-subsequence/

#include <vector>

using std::vector;

class Solution {
public:
    int lengthOfLIS(vector<int> &nums) {
        return lis(nums)
    }
};