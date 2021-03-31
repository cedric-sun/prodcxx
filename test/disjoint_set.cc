// https://leetcode.com/problems/graph-valid-tree/
#include <vector>

#define MAXN 2005
#include "../src/ds/disjoint-set.hpp"

using std::vector;

class Solution {
public:
    bool validTree(int n, const vector<vector<int>> &edges) {
        ds_init(n);
        for (const auto &edge : edges) {
            int a = ds_find(edge[0]), b = ds_find(edge[1]);
            if (a == b) {
                return false;
            }
            ds_join_leader(a, b);
        }
        return nset == 1;
    }
};
