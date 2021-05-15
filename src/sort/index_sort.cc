#include <bits/stdc++.h>
using namespace std;

// for unsorted array data[0,n-1], "sort" the integer sequence
// idx[0,n-1]: 1,2,...,n such that a[idx[]] is sorted

void dump(const vector<int> &data, const vector<int> &idx) {
    fputs("data:        ", stdout);
    for (int e : data) {
        printf("%6d", e);
    }
    putchar('\n');
    fputs("idx:         ", stdout);
    for (int e : idx) {
        printf("%6d", e);
    }
    putchar('\n');
    fputs("data[idx[]]: ",stdout);
    for (int e : idx) {
        printf("%6d",data[e]);
    }
    putchar('\n');
}

int main() {
    default_random_engine rng{random_device{}()};
    uniform_int_distribution<> uni;
    constexpr int MAXN = 100000;
    vector<int> data(MAXN);
    vector<int> idx(MAXN);
    for (int i = 0; i < MAXN; ++i) {
        data[i] = uni(rng);
        idx[i] = i;
    }
    sort(idx.begin(), idx.end(),
         [&data](const int &i1, const int &i2) { return data[i1] < data[i2]; });
    //dump(data, idx);
    int prev = INT_MIN;
    for (int i = 0; i < MAXN; ++i) {
        if (data[idx[i]] < prev) {
            putchar('?');
            break;
        }
        prev = data[idx[i]];
    }
    return 0;
}
