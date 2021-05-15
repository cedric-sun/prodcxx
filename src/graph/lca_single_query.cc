#include <bits/stdc++.h>
using namespace std;

// lc236. Single query LCA.

TreeNode *p, *q;

// return:
// 1. p or q if p or q (but not both) is found in the subtree rooted at `root`
// 2. LCA of p and q if both p and q are found in the subtree rooted at `root`
// 3. nullptr otherwise
TreeNode *dfs(TreeNode *root) {
    if (root) {
        if (root == p || root == q) {
            return root;
        }
        auto *left = dfs(root->left);
        auto *right = dfs(root->right);
        if (left && right)
            return root;
        return left == nullptr ? right : left;
    }
    return nullptr;
}

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    this->p = p;
    this->q = q;
    return dfs(root);
}
// ===================================================
// The same algorithm for n-ary tree with n >2

#define MAXN 10000

// vertex id in [1,MAXN]

int q0, q1;
vector<int> G[MAXN + 1];

// single query lca

// precond:
// 1. q0, q1 set to query points in any order,
// 2. G[u] contains v for all parent u having child v
int dfs(int u) {
    if (u == q0 || u == q1)
        return u;
    int cchild = -1;
    for (int i = 0;i<G[u].size();++i) {
        const int v = G[u][i];
        int x = dfs(v);
        if (x != -1) {
            if (cchild != -1) {
                return u; // the second time we found a non -1 return
            } else {
                cchild = x;
            }
        }
    }
    return cchild;
}

// poj 1330
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i)
            G[i].clear();
        // root is the one that never appears as v
        int vsum = 0;
        for (int i = 1; i < n; ++i) { // loop n-1 times
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            vsum += v;
        }
        int root = n * (n + 1) / 2 - vsum;
        // cout <<  "root = "<<root<<endl;
        cin >> q0 >> q1;
        cout << dfs(root) << endl;
    }
}

