#include <bits/stdc++.h>
using namespace std;

// [l,r] ; operator< must be defined for T
template <typename T> void qsort(vector<T> &a, int l, int r) {
    if (l < r) {
        const T gauge =
            a[l + (r - l) / 2]; // !! Can't be a reference. Must copy. !!
        int i = l - 1, j = r + 1;
        while (true) {
            do
                ++i;
            while (a[i] < gauge);
            do
                --j;
            while (gauge < a[j]); // we only use <
            if (i >= j)
                break;
            swap(a[i], a[j]);
        }
        qsort(a, l, j);
        qsort(a, j + 1, r);
    }
}

int main() {
    default_random_engine rng(random_device{}());
    uniform_int_distribution<> uni{};
    constexpr int MAXN = 100000;
    vector<int> data(MAXN), ref(MAXN);
    for (int t = 0; t < 15; t++) {
        for (int i = 0; i < MAXN; i++) {
            ref[i] = data[i] = uni(rng);
        }
        sort(ref.begin(), ref.end());
        qsort(data, 0, data.size() - 1);
        if (ref != data) {
            puts("?");
            break;
        }
    }
    return 0;
}
