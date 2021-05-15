#include <bits/stdc++.h>

using namespace std;

// inversion is a measure over a sequence describing "how far this sequence is
// from its sorted version".
long ninv_left, ninv_right; // note that for array of size 100k, # of
                            // inversions can easily overflow int32.

// The following code demonstrate 3 equivalent ways to count the # of inversion
// pair:
// 1. ninv, the accumulated return value. This is essentially the same as
// ninv_right
// 2. ninv_right, a global accumulator that is added to everytime we spit from a
// right part
// 2. ninv_left, a global accumulator that is added to everytime we spit from a
// left part

// precond: data[l,m) sorted && data[m,r) sorted
// postcond: aux[l,r) overwritten and sorted;
// [l,r)
long merge(vector<int> &data, vector<int> &aux, int l, int m, const int r) {
    const int cm = m;
    long ninv = 0;
    int k = l;
    // Every time we spit from left, we know
    //      Current left element form an inversion with each already-spitted
    //      right element. thus
    //              ninv_left += m - cm
    // Every time we spit from right, we know
    //      Current right element form an inversion with each remaining left
    //      element.thus
    //              ninv_right += cm - l;
    while (l < cm && m < r) {
        if (data[l] <= data[m]) { // <= for stablity
            aux[k++] = data[l++];
            // everytime we spit from left, all already spitted right elements
            // are inversion;
            ninv_left += m - cm;
        } else {
            aux[k++] = data[m++];
            // everytime we spit from right, all currently
            // remaining left elements are inversion
            ninv += cm - l;
            ninv_right += cm - l;
        }
    }

    // End game merging: now either left or right is completely spitted,
    // we finish whichever part that remains.
    // 
    // We still needs to update the inversion counter, but interesting things
    // happen for ninv_right: We want update `ninv_right += cm - l` every time
    // we spit from right. But since we are spitting from right, we are sure
    // that left is empty, i.e. cm - l is always 0. Thus nothing needs to be
    // done with ninv_right in the `while(m < r)` loop.
    while (l < cm) {
        ninv_left += m - cm;
        aux[k++] = data[l++];
    }
    while (m < r)
        aux[k++] = data[m++];
    return ninv;
}

// precond: data[l,r) == aux[l,r)
// postcond: aux[l,r) sorted
// [l,r)
long split(vector<int> &data, vector<int> &aux, int l, int r) {
    long ninv = 0;
    if (r - l > 1) { // no work to be done if diff by 1
        int mid = (l + r) / 2;
        ninv += split(aux, data, l, mid);
        ninv += split(aux, data, mid, r);
        ninv += merge(data, aux, l, mid, r);
    }
    return ninv;
}

int merge_sort(vector<int> &data, vector<int> &aux) {
    aux = data;
    return split(aux, data, 0, data.size());
}

int main() {
    default_random_engine rng{random_device{}()};
    uniform_int_distribution<> uni;
    constexpr int MAXN = 100000;
    vector<int> data(MAXN), aux(MAXN), ans(MAXN);
    for (int i = 0; i < 15; i++) {
        // WARNING: aux needs to be initialized identical to data
        for (int j = 0; j < MAXN; j++) {
            ans[j] = data[j] = uni(rng);
        }
        ninv_left = ninv_right = 0;
        int ninv = merge_sort(data, aux);
        sort(ans.begin(), ans.end());
        if (data != ans) {
            puts("?");
            break;
        }
        printf("ninv: %ld, ninv_left: %ld, ninv_right: %ld, \n", ninv,
               ninv_left, ninv_right);
    }
    return 0;
}
