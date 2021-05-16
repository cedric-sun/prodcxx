#include <bits/stdc++.h>

using namespace std;

// 0-based segment tree. i.e. left = root*2+1, right = root*2+2

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

    // precond: [i,j] is completely inside [l,r]
    // return: property of interest over segment data[i,j]
    int seg_query(const int root, const int l, const int r, const int i,
                  const int j) const {
        // WARNING: I don't think the following 2 lines are possible.
//        if (l > j || r < i)   // [l,r] not even touching [i,j]
//            return 0;         // return a proper sentinel value
        if (i <= l && r <= j) // [l,r] is completely inside [i,j]
            return seg[root]; // return whole segment
        const int m = l + (r - l) / 2;
        // left half is [l,m], right half is [m+1,r]
        if (i > m) // [i,j] is completely in the right half of [l,r]
            return seg_query(root * 2 + 2, m + 1, r, i, j); // goes right
        else if (j <= m) // [i,j] is completely in the left half of [l,r]
            return seg_query(root * 2 + 1, l, m, i, j); // goes left
        // When [i,j] span across m, we divide [i,j] as well for subquery.
        // Thus [i,j] in each stack frame is always complete inside [l,r].
        // i.e. (i<=l<=j && r>j) and (i<=r<=j && l<i) are impossible.
        //
        // Thus we ensured, in each stack frame, [i,m] is completely inside [l,m],
        // and [m+1,j] is completely inside [m+1,r]
        int res_left = seg_query(root * 2 + 1, l, m, i, m);
        int res_right = seg_query(root * 2 + 2, m + 1, r, m + 1, j);

        // merge query result, e.g. sum
        return res_left + res_right;
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
        if (i > m)
            seg_update(root * 2 + 2, m + 1, r, i, val); // goes right
        else
            seg_update(root * 2 + 1, l, m, i, val); // goes left
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
