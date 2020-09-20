// cesun, 9/7/20 2:41 PM.

#include <cstring>

// merge by size, path compression, memset init
struct disjoint_set {
    int *const arr;
    int n_set; // number of separated sets;

    // index is [0,n)
    disjoint_set(const int n) : arr(new int[n]),n_set(n) {
        memset(arr, -1, sizeof(*arr) * n);
    }

    int find(int x) {
        // n=2^63 to overflow this buffer
        static int stack[64], top = 0;
        while (arr[x] >= 0) {
            stack[top++] = x;
            x = arr[x];
        }
        while (top) arr[stack[--top]] = x;
        return x;
    }

    //PRECONDITION: a = uf(x); b=uf(y); a != b
    void join_leader(const int a, const int b) {
        if (arr[a] <= arr[b]) {
            arr[a] += arr[b];
            arr[b] = a;
        } else {
            arr[b] += arr[a];
            arr[a] = b;
        }
        --n_set;
    }

    void join(const int x, const int y) {
        const int a = find(x), b = find(y);
        if (a != b) {
            join_leader(a, b);
        }
    }

    virtual ~disjoint_set() {
        delete[] arr;
    }
};


// unit test: https://leetcode.com/problems/graph-valid-tree/
#include <vector>

using std::vector;

class Solution {
public:
    bool validTree(int n, const vector<vector<int>> &edges) {
        disjoint_set ds{n};
        for (const auto &edge : edges) {
            int a = ds.find(edge[0]), b = ds.find(edge[1]);
            if (a == b) {
                return false;
            }
            ds.join_leader(a, b);
        }
        return ds.n_set == 1;
    }
};
