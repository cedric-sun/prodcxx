#include <bits/stdc++.h>

using namespace std;

// 0-based segment tree. i.e. left = root*2+1, right = root*2+2

// Same as seg_tree_proto, but better query handling!

class seg_tree {
private:
    const int n;
    vector<int> seg;

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

    int seg_query(const int root, const int l, const int r, const int i,
                  const int j) const {
        if (i <= l && r <= j) // [l,r] is completely inside [i,j]
            return seg[root]; // return whole segment
        const int m = l + (r - l) / 2;
        int sum = 0;
        if (i <= m) // [i,j] overlap with left part, i.e. [l,m]
            sum += seg_query(root * 2 + 1, l, m, i, j); // query left
        if (j > m) // [i,j] overlap with right part, i.e. [m+1,r]
            sum += seg_query(root * 2 + 2, m + 1, r, i, j); // query right
        return sum;
    }

    // update data[i] = val
    void seg_update(const int root, const int l, const int r, const int i,
                    const int val) {
        if (l == r) {
            seg[root] = val;
            return;
        }
        const int m = l + (r - l) / 2;
        // left half is [l,m], right half is [m+1,r]
        if (i <= m)
            seg_update(root * 2 + 1, l, m, i, val); // goes left
        else
            seg_update(root * 2 + 2, m + 1, r, i, val); // goes right
        // update all ancestors, e.g. sum
        seg[root] = seg[root * 2 + 1] + seg[root * 2 + 2];
    }

public:
    seg_tree(const vector<int> &data) : n{(int) data.size()} {
        // we don't care about the value in the grown space, though they are 0.
        // Those cell will never be accessed.
        seg.resize(4 * n);
        seg_build(0, 0, n - 1, data);
    }

    // query [l,r]
    int query(const int i, const int j) const {
        return seg_query(0, 0, n - 1, i, j);
    }

    void update(const int i, const int val) {
        seg_update(0, 0, n - 1, i, val);
    }
};


//  ================ unit test
class NumArray {
public:
    seg_tree a;
    NumArray(vector<int>& nums):a{nums} {

    }

    void update(int index, int val) {
        a.update(index, val);
    }

    int sumRange(int left, int right) {
        return a.query(left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
