#include <bits/stdc++.h>

using namespace std;

class seg_tree_lazy_assign {
private:
    const int n;
    vector<int> seg;
    vector<int> lazy; // lazy[i]: pending value to be assign to children if dig
                      // further from seg[i]
    vector<char> is_lazy; // we must use a flag array (or a sentinel value in
                          // lazy[]), since, not like lazy delta, lazy[i] == 0
                          // doesn't means no-op. It means assigning all leaves
                          // in this subtree to be 0;

    void seg_build(const int root, const int l, const int r,
                   const vector<int> &data) {
        if (l == r) {
            seg[root] = data[l];
            return;
        }
        const int m = l + (r - l) / 2;
        seg_build(root * 2 + 1, l, m, data);
        seg_build(root * 2 + 2, m + 1, r, data);
        seg[root] = seg[root * 2 + 1] + seg[root * 2 + 2];
    }

    inline void push_down(const int root, const int l, const int r,
                          const int m) {
        lazy[root * 2 + 1] = lazy[root * 2 + 2] = lazy[root];
        seg[root * 2 + 1] = (m - l + 1) * lazy[root];
        seg[root * 2 + 1] = (r - m) * lazy[root];
        lazy[root] = 0; // zeroing lazy[root] is not necessary, since we clear
                        // the is_lazy[root] mark once return
    }

    // function invariant: everytime we visit a node, its seg[] is up-to-date,
    // but its is_lazy[] might be true
    void seg_range_update_assign(const int root, const int l, const int r,
                                 const int i, const int j, const int val) {
        if (i <= l && r <= j) {
            seg[root] = (r - l + 1) * val;
            lazy[root] = val; // this might mark a leaf as lazy, but we always
                              // return in this block for leaf, so safe
            is_lazy[root] = true;
            return;
        }
        const int m = l + (r - l) / 2;
        if (is_lazy[root]) {
            push_down(root, l, r, m);
            is_lazy[root] = false;
        }
        if (i <= m)
            seg_range_update_assign(root * 2 + 1, l, m, i, j, val); // left
        if (j > m)
            seg_range_update_assign(root * 2 + 2, m + 1, r, i, j, val); // right
        seg[root] = seg[root * 2 + 1] + seg[root * 2 + 2];
    }

    int seg_query(const int root, const int l, const int r, const int i,
                  const int j) {
        if (i <= l && r <= j)
            return seg[root];
        const int m = l + (r - l) / 2;
        if (is_lazy[root]) {
            push_down(root, l, r, m);
            is_lazy[root] = false;
        }
        int sum = 0;
        if (i <= m)
            sum += seg_query(root * 2 + 1, l, m, i, j); // left
        if (j > m)
            sum += seg_query(root * 2 + 2, m + 1, r, i, j); // right
        return sum;
    }

public:
    seg_tree_lazy_assign(const vector<int> &data) : n{(int)data.size()} {
        seg.resize(4 * n);
        lazy.resize(4 * n);
        is_lazy.assign(4 * n, false);
        seg_build(0, 0, n - 1, data);
    }

    // assign data[i,j] to be val; single position update can be
    // `update(i,i,val)`;
    void update(const int i, const int j, const int val) {
        seg_range_update_assign(0, 0, n - 1, i, j, val);
    }

    // range sum [i,j]
    int query(const int i, const int j) { return seg_query(0, 0, n - 1, i, j); }
};

// =========== unit test =================

class NumArray {
public:
    seg_tree_lazy_assign a;

    NumArray(vector<int> &nums) : a{nums} {}

    void update(int index, int val) { a.update(index, index, val); }

    int sumRange(int left, int right) { return a.query(left, right); }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
