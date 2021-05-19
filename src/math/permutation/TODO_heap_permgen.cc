#include <bits/stdc++.h>
using namespace std;

namespace heaps_permgen_recursive {
vector<vector<int>> ans;

// call with heaps(a.size()-1.a);
void heaps(int n, vector<int> &a) {
    if (n == 0) {
        ans.push_back(a);
        return;
    }
    for (int i = 0; i <= n; ++i) {
        heaps(n - 1);
        if (n % 2 == 1) { // n is odd
            swap(a[i], a[n])
        } else {
            swap(a[0], a[n])
        }
    }
}
} // namespace heaps_permgen_recursive

namespace heaps_permgen_iterative {
// an interative implementation of the heap's permutation generation algorithm.
// TODO
void heaps_permgen_iterative(vector<int> &a) {
    const int n = a.size();
    vector<int> p(n), c(n);
}
} // namespace heaps_permgen_iterative
