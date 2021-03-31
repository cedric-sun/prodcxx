// Created by cesun on 3/20/21.

#define MAXN 3000
#define MAX_QUERIES 1000
#include "../src/graph/lca_tarjan_offline.hpp"

//lc236 https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {

    }
};