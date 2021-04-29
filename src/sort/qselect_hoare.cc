#include <bits/stdc++.h>
using namespace std;

// std::nth_element(first, it, last):
// 1.*it be the exact element as if [first,last) were sorted
// 2. all prefix elements in [first, it) is smaller than *(it)
// i.e. find the (it-first+1) smallest elements; for `it = first+n`,
// it's finding the (n+1)-th smallest element

// This implementation does the same except off-by-one,
// i.e. find the k smallest elements, result in a[0,k)
// after return, a[k-1] be the exact n-th smallest element, with
// a[l,k) be smaller than a[k]
// [l,r]
void qselect_kmin(vector<int> &a, const int l, const int r, const int k) {
    if (l < r) {
        int gauge = a[l + (r - l) / 2];
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
        const int lsize = j + 1;
        if (lsize >= k) { // it's crucial to still go left when lsize == k
            qselect_kmin(a, l, j, k); // goes left
        } else {
            qselect_kmin(a, j + 1, r, k); // goes right
        }
    }
}

// a slight variant, natively find the k largest elements, result in a[n-k,n)
//
// Compare to qselect_kmin(..., n-k+1), qselect_kmax(..., k) use less
// comparisons if k is much smaller than n
void qselect_kmax(vector<int> &a, const int l, const int r, const int k) {
    if (l < r) {
        int gauge = a[l + (r - l) / 2];
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
        const int rsize = a.size() - j - 1;
        if (rsize < k) {
            qselect_kmax(a, l, j, k); // goes left
        } else { // it's crucial to still go right when rsize == k
            qselect_kmax(a, j + 1, r, k); // goes right
        }
    }
}

void dump(vector<int> &a, const string id) {
    puts(id.c_str());
    for (int i = 0; i < a.size(); i++) {
        printf("%4d", i);
    }
    putchar('\n');
    for (int i = 0; i < a.size(); i++) {
        printf("%4d", a[i]);
    }
    putchar('\n');
}

void test_qselect_kmin() {
    default_random_engine rng(random_device{}());
    uniform_int_distribution<> uni{};
    constexpr int MAXN = 100000;
    vector<int> data(MAXN), ref(MAXN);
    for (int t = 0; t < 15; t++) {
        for (int i = 0; i < MAXN; i++) {
            ref[i] = data[i] = uni(rng);
        }
        const int k = MAXN * 3 / 4;
        // printf("k = %d\n", k);

        // We find k smallest elements on both ref and data.
        // partially sort ref[0,k-1] with ref[k-1] be the exact k-th smallest
        nth_element(ref.begin(), ref.begin() + k - 1, ref.end());
        // find the k smallest element
        qselect_kmin(data, 0, data.size() - 1, k);

        // dump(data, "data before sort");
        // dump(ref, "ref before sort");

        if (ref[k - 1] != data[k - 1]) {
            printf("ref[%d] != data[%d]", k - 1, k - 1);
            break;
        }

        data.resize(k);
        ref.resize(k);
        sort(ref.begin(), ref.end());
        sort(data.begin(), data.end());
        // dump(data, "data");
        // dump(ref, "ref");
        if (ref != data) {
            puts("?");
            break;
        }
    }
}

void test_qselect_kmax() {
    default_random_engine rng(random_device{}());
    uniform_int_distribution<> uni{};
    constexpr int MAXN = 100000;
    vector<int> data(MAXN), ref(MAXN);
    for (int t = 0; t < 15; t++) {
        for (int i = 0; i < MAXN; i++) {
            ref[i] = data[i] = uni(rng);
        }
        const int k = MAXN * 3 / 4;
        //printf("k = %d\n", k);

        // We find k largest elements on both ref and data.
        // partially sort ref[0,n-k] with ref[n-k] be the exact k-th smallest,
        // thus also the k-th largest, and ref[n-k,n) be the k largest elements
        const int n = ref.size();
        nth_element(ref.begin(), ref.begin() + n - k, ref.end());
        // find the k largest element
        qselect_kmax(data, 0, data.size() - 1, k);

        //dump(data, "data before sort");
        //dump(ref, "ref before sort");

        if (ref[n - k] != data[n - k]) {
            printf("ref[%d] != data[%d]\n", n - k, n - k);
            break;
        }

        vector<int> cropdata(data.begin() + n - k, data.end());
        vector<int> cropref(ref.begin() + n - k, ref.end());
        sort(cropdata.begin(), cropdata.end());
        sort(cropref.begin(), cropref.end());
        //dump(data, "cropdata sorted");
        //dump(ref, "cropref sorted");
        if (cropdata != cropref) {
            puts("?");
            break;
        }
    }
}

int main() {
    test_qselect_kmin();
    test_qselect_kmax();
}
