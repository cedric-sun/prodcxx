#include <bits/stdc++.h>

using namespace std;


// Sometimes we want range-based update on a segment tree,
// e.g. add 40 to each element in data[15,120] or set all element in data[15,120] to 40
// For a normal segment tree, we can turn such range-based into multiple single position update, which is slow.

// a lazy segment tree is a segment tree that support efficient range-based update.
// TODO: verify correctness

class seg_tree_lazy {
private:
    const int n;
    vector<int> seg;
    vector<int> lazy;

    // tree-building is the same
    // [l,r]
    void seg_build(const int root, const int l,
                   const int r, const vector<int> &data) {
        if (l == r) {
            seg[root] = data[l];
            return;
        }
        const int m = l + (r - l) / 2;
        seg_build(root * 2 + 1, l, m, data);
        seg_build(root * 2 + 2, m + 1, r, data);
        // merge: e.g. sum
        seg[root] = seg[root * 2 + 1] + seg[root * 2 + 2];
    }

    // TODO: verify correctness
    // add delta to each data[i,j]
    void seg_range_update(const int root, const int l, const int r, const int i, const int j, const int delta) {
        if (i <= l && r <= j) { // [i,j] completely contains current segment [l,r]
            // mark lazy and done
            seg[root] += (r - l + 1) * delta;
            lazy[root] = delta;
            return;
        }
        // now we know [i,j] doesn't completely contain [l,r], but at least they overlap.
        // Thus we must dive deeper, potentially to either left half of [l,r], or right half, or both.
        // Thus we must push down any laziness at the current root.
        const int m = l + (r - l) / 2;
        if (lazy[root] != 0 && l != r) { // if current node has lazy, and its not leaf
            seg[root] += lazy[root] * (r - l + 1);
            lazy[root * 2 + 1] += lazy[root];
            lazy[root * 2 + 2] += lazy[root];
            lazy[root] = 0;
        }
        if (i <= m)
            seg_range_update(root * 2 + 1, l, m, i, j, delta); // left
        if (j > m)
            seg_range_update(root * 2 + 2, m + 1, r, i, j, delta); //right
        seg[root] = seg[root * 2 + 1] + seg[root * 2 + 2];
    }

public:
    seg_tree_lazy(const vector<int> &data) : n{(int) data.size()} {
        seg.resize(4 * n);
        lazy.reserve(4 * n);
        seg_build(0, 0, n - 1, data);
    }

    int query(int i, int j) const {

    }

    void update(int i, int val) {

    }

    void update(int i, int j, int delta) {
        seg_range_update(0, 0, n - 1, i, j, delta);
    }
};