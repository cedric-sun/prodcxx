#include <bits/stdc++.h>
using namespace std;

// all farthest smaller/larger value has the following form:
//
// Given an array a[] of size n, for each position i return the index of the
// leftmost/rightmost element that is smaller(or equal)/greater(or equal) than
// a[i];

namespace when_values_in_a_is_small {
// when all a[i] are in a reasonable range say a[i] <= 30000,
// we can compute the afsv problem in O(n) using the thought similar
// to a counting sort.
//
// Variants:
//      For rightmost, we can use suffix max.
//      For smaller equal, we can use prefix min;
//      For strictly larger situation, we can do exclusive rolling suffix min
vector<int> leftmost_larger_equal(const vector<int> &a) {
    int max_ai = INT_MIN;
    for (int e : a)
        max_ai = max(max_ai, e);
    // allocate an array of of size max(a[i]) +1
    vector<int> leftmost(max_ai + 1, INT_MAX);
    for (int i = a.size() - 1; i >= 0; --i) {
        // for identical value in a[], we want the index of the leftmost one,
        // thus we do a backward scan
        leftmost[a[i]] = i;
    }
    // we want find the leftmost j (i.e. smallest i) such that a[j]>a[i].
    // This can be done by finding the minimum value in leftmost[a[i],max_ai]
    // i.e. query the minimum of a suffix of leftmost[].
    // We can do a rolling min and answer each query in O(1);
    for (int i = max_ai - 1; i >= 0; i--) {
        // inclusive rolling suffix min
        leftmost[i] = min(leftmost[i], leftmost[i + 1]);
    }
    // index of the leftmost element that is larger than or equal to a[i] is
    // leftmost[a[i]]; (when a[i] is largest element we find itself)
    vector<int> ans(a.size());
    for (int i = 0; i < a.size(); ++i)
        ans[i] = leftmost[a[i]];
    return ans;
}

} // namespace when_values_in_a_is_small

namespace compare_based {
// if the range of values in a[] is INT_MIN to INT_MAX,
// we can't allocate an array that large. Instead we use binary search
// on the array.
vector<int> leftmost_larger_equal(const vector<int> &a) {
    const int n = a.size();
    vector<int> pfx_max(n); // inclusive suffix min
    pfx_max[0] = a[0];
    for (int i = 1; i < a.size(); ++i)
        pfx_max[i] = max(pfx_max[i - 1], a[i]);
    vector<int> ans(a.size());
    for (int i = 0; i < n; ++i)
        ans[i] =
            lower_bound(pfx_max.begin(), pfx_max.end(), a[i]) - pfx_max.begin();
    return ans;
}

} // namespace compare_based

void test(const vector<int> &a) {
    auto ans1 = when_values_in_a_is_small::leftmost_larger_equal(a);
    auto ans2 = compare_based::leftmost_larger_equal(a);
    if (ans1 != ans2) {
        puts("?");
        return;
    }
    //for (int e : ans1)
    //    cout << e << ' ';
    //cout << endl;
}
int main() {
    constexpr int MAXN = 100000;
    default_random_engine rng(random_device{}());
    uniform_int_distribution<> uni{0, 30000};
    vector<int> data(MAXN);
    for (int T = 0; T < 15; T++) {
        for (int i = 0; i < MAXN; ++i)
            data[i] = uni(rng);
        test(data);
    }
    return 0;
}
