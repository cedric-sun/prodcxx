// For unsorted array a[] of size n, the # of inversion pairs that a[i]
// is part of (i.e. i<j && a[i]>a[j] or k<i && a[k]>a[i]),
// is the # of trailing smaller elements of a[i], plus the # of 
// preceding larger elements.
//
// That is, # of inversions per element is the sum of the 2 ans[] arrays
// in both namespace.

#include <bits/stdc++.h>
using namespace std;

// This code demonstrate that the inversion counting while doing merge sort can
// be done in a per-element basis, i.e. Given unordered array a[] of size n, for
// each a[i] we can find:
// 1. # of larger elements before a[i]
// 2. # of smaller elements after a[i]
// using merge sort.

// we want sort the original elements, but we also want to know, for each
// element what's its index in the original array, thus the vi.
//
// We can even omit this vi structure by sorting an ordered sequence
// [0,1,2,...,n-1] i.e. the index w.r.t to the element array (the index sort).
struct vi {
    int val, i;
};

namespace number_of_larger_element_before_each_ai {
// ans[i]: # of larger element before a[i]
int ans[100000];

void merge_sort(vector<vi> &data, vector<vi> &aux, int l, const int r) {
    if (r - l > 1) {
        const int cm = l + (r - l) / 2;
        merge_sort(aux, data, l, cm);
        merge_sort(aux, data, cm, r);
        int m = cm, k = l;
        while (l < cm && m < r) {
            if (data[l].val <= data[m].val) {
                aux[k++] = data[l++];
            } else {
                // we update ans[current_element.i] when spitting from right.
                //
                // When we spit an element from right,
                // we know that all remaining elements in the left
                // is larger than self, thus all of them count as
                // preceding larger elements
                ans[data[m].i] += cm - l;
                aux[k++] = data[m++];
            }
        }
        while (l < cm) {
            aux[k++] = data[l++];
        }
        while (m < r) {
            // no need to update ans since left is always empty,
            // i.e. cm - l is always 0
            aux[k++] = data[m++];
        }
    }
}

vector<int> solve(const vector<int> &a) {
    memset(ans, 0, sizeof ans);
    const int n = a.size();
    vector<vi> data(n), aux(n);
    for (int i = 0; i < n; ++i)
        data[i] = aux[i] = {a[i], i};
    merge_sort(data, aux, 0, n);
    return vector<int>(ans, ans + n);
}
} // namespace number_of_larger_element_before_each_ai

// We can find the # of smaller element after each a[i] by a simple
// modification, i.e. the place where update the count, instead of in the branch
// where we spit from right, we now update the count when we spit from left.
//
// See lc315 for identical problem
// https://leetcode.com/problems/count-of-smaller-numbers-after-self/
namespace number_of_smaller_element_after_each_ai {

int ans[100000];

void merge_sort(vector<vi> &data, vector<vi> &aux, int l, const int r) {
    if (r - l > 1) {
        const int cm = l + (r - l) / 2;
        merge_sort(aux, data, l, cm);
        merge_sort(aux, data, cm, r);
        int m = cm, k = l;
        while (l < cm && m < r) {
            if (data[l].val <= data[m].val) {
                // we udpate ans[current_element.i] when spitting from left
                //
                // When we spit from left, we know that all spitted
                // elements in the right are smaller than self,
                // thus all of them count as trailing smaller elements.
                ans[data[l].i] += m - cm;
                aux[k++] = data[l++];
            } else {
                aux[k++] = data[m++];
            }
        }
        while (l < cm) {
            // don't forget to also update ans[] here, since
            // m-cm is not zero; (but yes m-cm a constant now)
            ans[data[l].i] += m - cm;
            aux[k++] = data[l++];
        }
        while (m < r)
            aux[k++] = data[m++];
    }
}

vector<int> solve(const vector<int> &a) {
    memset(ans, 0, sizeof ans);
    const int n = a.size();
    vector<vi> data(n), aux(n);
    for (int i = 0; i < n; ++i)
        data[i] = aux[i] = {a[i], i};
    merge_sort(data, aux, 0, n);
    return vector<int>(ans, ans + n);
}
} // namespace number_of_smaller_element_after_each_ai
