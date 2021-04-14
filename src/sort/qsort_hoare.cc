#include <bits/stdc++.h>
using namespace std;

// [l,r]
void qsort_hoare(vector<int> &a, int l, int r) {
    if (l < r) {
        int gauge = a[(l + r) >> 1]; // pick gauge in the middle
        int i = l - 1, j = r + 1;
        while (true) {
            do {
                ++i;
            } while (a[i] < gauge);
            do {
                --j;
            } while (a[j] > gauge);
            if (i >= j)
                break;
            swap(a[i], a[j]);
        }
        // now [l,j] <= gauge && [j+1,r] >= gauge
        qsort_hoare(a, l, j);
        qsort_hoare(a, j + 1, r);
    }
}

int main() {
    default_random_engine rng{random_device{}()};
    uniform_int_distribution<> uni{};
    constexpr int N = 20000;
    vector<int> data;
    vector<int> ans{data};
    data.reserve(N);
    constexpr int NTEST = 15;
    for (int k = 0; k < NTEST; k++) {
        data.clear();
        for (int i = 0; i < N; i++)
            data.push_back(uni(rng));
        ans = data;
        qsort_hoare(data, 0, data.size() - 1);
        sort(ans.begin(), ans.end());
        if (ans != data) {
            puts("?");
            break;
        }
    }
    return 0;
}
