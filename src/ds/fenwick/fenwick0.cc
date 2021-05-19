#include <bits/stdc++.h>

using namespace std;

// 1-based fenwick tree for prefix sum

int n; // # of elements in data[]
vector<int> fenwick; // 1-based  [1,n]

inline int lowbit(const int x) { return x & -x; }

void fw_add(int i, const int delta) {
    while (i <= n) {
        fenwick[i] += delta;
        i += lowbit(i);
    }
}

// prefix sum [1,i]; fw_query(0) = 0;
int fw_query(int i) {
    int ans = 0;
    while (i >= 1) {
        ans += fenwick[i];
        i -= lowbit(i);
    }
    return ans;
}

int main() {

}
