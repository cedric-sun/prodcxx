#include <bits/stdc++.h>

using namespace std;

// inversion is a measure over a sequence describing "how far this sequence is from its sorted version".
int ninv2;

// precond: data[l,m) sorted && data[m,r) sorted
// postcond: aux[l,r) overwritten and sorted;
// [l,r)
int merge(vector<int> &data, vector<int> &aux, int l, int m, const int r) {
    const int mm = m;
    int ninv = 0;
    int k = l;
    while (l < mm && m < r) {
        if (data[l] <= data[m]) { // <= for stablity
            aux[k++] = data[l++];
        } else {
            aux[k++] = data[m++];
            ninv += (mm - l);
            ninv2 += (mm - l);
        }
    }
    while (l < mm)
        aux[k++] = data[l++];
    while (m < r)
        aux[k++] = data[m++];
    return ninv;
}

// precond: data[l,r) == aux[l,r)
// postcond: aux[l,r) sorted
// [l,r)
int split(vector<int> &data, vector<int> &aux, int l, int r) {
    int ninv = 0;
    if (r - l > 1) { // no work to be done if diff by 1
        int mid = (l + r) / 2;
        ninv += split(aux, data, l, mid);
        ninv += split(aux, data, mid, r);
        ninv += merge(data, aux, l, mid, r);
    }
    return ninv;
}

int merge_sort(vector<int> &data, vector<int> &aux) {
    aux = data;
    return split(aux, data, 0, data.size());
}

int main() {
    default_random_engine rng{random_device{}()};
    uniform_int_distribution<> uni;
    constexpr int MAXN = 1000;
    vector<int> data(MAXN), aux(MAXN), ans(MAXN);
    for (int i = 0; i < 15; i++) {
        // WARNING: aux needs to be initialized identical to data
        for (int j = 0; j < MAXN; j++) {
            ans[j] = data[j] = uni(rng);
        }
        ninv2 = 0;
        int ninv = merge_sort(data, aux);
        sort(ans.begin(), ans.end());
        if (data != ans) {
            puts("?");
            break;
        }
        printf("ninv: %d, ninv2: %d\n", ninv, ninv2);
    }
    return 0;
}
