// cesun, 9/17/20 12:10 PM.

namespace iqsort {
    static int *arrr;

    // upper bound to minimize number of elements need to be moved.
    // search [l,r)
    static inline int upper_bound(int l, int r, const int k) {
        while (l < r) {
            int m = (l + r) >> 1; // or l+((n-l)>>1)
            if (arrr[m] > k) r = m;
            else l = m + 1;
        }
        return l;
    }

    // [l,r)
    static inline void insertion_sort(int l, int r) {
        for (int i = l + 1; i < r; ++i) {
            // [l,i) is sorted
            const int x = arrr[i];
            const int iidx = upper_bound(l, i, x);
            for (int j = i; j > iidx; --j) {
                arrr[j] = arrr[j - 1];
            }
            arrr[iidx] = x;
        }
    }

    //TODO: non-recursive (and maybe parallel)
    static void _qsort(int l, int r) {
        if (l < r) {
            if (r - l < 16) {
                insertion_sort(l, r + 1);
            } else {
                int gauge = arrr[(l + r) >> 1];
                int i = l - 1, j = r + 1;
                for (;;) {
                    while (arrr[++i] < gauge);
                    while (arrr[--j] > gauge);
                    if (i >= j) break;
                    int tmp = arrr[i];
                    arrr[i] = arrr[j];
                    arrr[j] = tmp;
                }
                _qsort(l, j);
                _qsort(j + 1, r);
            }
        }
    }

    static inline void qsort(int *arr, int n) {
        arrr = arr;
        _qsort(0, n - 1);
    }
}

#include <cstdio>
#include <random>
#include <algorithm>
#include <array>
#include <memory>

using std::vector;

#define TST_SIZE 5000
#define TST_N 15
using TestArrayT = std::array<int, TST_SIZE>;

// std::sort can work on c-style raw array though ...

bool test_insertion_sort(TestArrayT &data) {
    //todo forward? when is this unique_ptr dereferenced?
    auto dataCopyPtr = std::make_unique<TestArrayT>(data);
    std::sort(dataCopyPtr->begin(), dataCopyPtr->end());
    iqsort::arrr = data.data();
    iqsort::insertion_sort(0, TST_SIZE);
    if (data != *dataCopyPtr) {
        putchar('x');
        return false;
    }
    return true;
}

bool test_qsort(TestArrayT &data) {
    auto dataCopyPtr = std::make_unique<TestArrayT>(data);
    std::sort(dataCopyPtr->begin(), dataCopyPtr->end());
    iqsort::qsort(data.data(), data.size());
    if (data != *dataCopyPtr) {
        putchar('x');
        return false;
    }
    return true;
}

//TODO: benchmark
int main() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution randint;

    auto dataPtr = std::make_unique<TestArrayT>();
    for (int i = 0; i < TST_N; ++i) {
        for (int j = 0; j < TST_SIZE; ++j) {
            (*dataPtr)[j] = randint(generator);
        }
        //test_insertion_sort(*dataPtr);
        test_qsort(*dataPtr);
    }
}
