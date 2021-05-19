// https://en.wikipedia.org/wiki/All_nearest_smaller_values

#include <cstdio>
#include <functional>
#include <vector>

using std::vector;

// ANSV keywords: for each element in the sequence, find the next/previous
// greater/smaller element.
// ANSV can be an embeded subproblem for many problem. See lc84 for an example.

namespace stack_based_ansv {
vector<int> ansv(const vector<int> &x) {
    // TODO: mono stack based
}
} // namespace stack_based_ansv

namespace jump_path_compression_ansv { // Jump Path Compression base ANSV.

// return P[x.size()] such that x[P[i]] < x[i], and i-P[i] is minimal
// If no such P[i] exists, P[i] is -1
vector<int> left_nearest_smaller(const vector<int> &x) {
    vector<int> ans(x.size());
    for (int i = 0; i < x.size(); ++i) {
        int j = i - 1;
        // for all nearest larger value, change x[j] >= x[i] to x[j] <= x[i]
        // for non-strict smaller/larger, remove the equality
        while (j >= 0 && x[j] >= x[i])
            j = ans[j];
        ans[i] = j;
    }
    return ans;
}

// A template one demonstrating solvable variants.
//
// Take care if you pass in reverse iterators, the return will be reversed
// index, i.e. 0 is the last last element. To change that into normal indexes,
// 1. either
//      a) apply `a.size() - value - 1` for each non-(-1) value in returned
//      vector, and still treat -1 as sentinel value, or
//      b) apply `a.size() - value - 1` for each value unconditionally, and
//      treat a.size() as sentinel value. (this one is sometimes very useful)
// 2. then reverse the returned vector.
//
// See lc739 for a reverse-greater example.
//
// | iterator\comp | less                      | greater                  |
// |---------------+---------------------------+--------------------------|
// | forward       | nearest preceding smaller | nearest preceding larger |
// | reverse       | nearest following smaller | nearest following larger |
template <typename RandomIt,
          typename Comp =
              std::less<typename std::iterator_traits<RandomIt>::value_type>>
vector<int> ansv_template(RandomIt begin, RandomIt end, Comp comp = Comp()) {
    const int n = distance(begin, end);
    vector<int> ans(n);
    RandomIt it0 = begin;
    while (it0 != end) {
        RandomIt it1 = it0 - 1;
        while (it1 >= begin &&
               (comp(*it0, *it1) || !comp(*it0, *it1) && !comp(*it1, *it0))) {
            it1 = ans[it1 - begin] + begin;
        }
        ans[it0 - begin] = it1 - begin;
        ++it0;
    }
    return ans;
}

void test(const vector<int> &data) {
    fputs("data:     ", stdout);
    for (int value : data)
        printf("%4d", value);
    putchar('\n');
    fputs("idx:      ", stdout);
    vector<int> idxes = left_nearest_smaller(data);
    vector<int> idxes2 = ansv_template(data.cbegin(), data.cend());
    if (idxes != idxes2) {
        puts("?");
        return;
    }
    for (int i : idxes) {
        printf("%4d", i);
    }
    putchar('\n');
    fputs("data[idx]:", stdout);
    for (int i : idxes) {
        if (i < 0)
            fputs("   -", stdout);
        else
            printf("%4d", data[i]);
    }
    putchar('\n');
    putchar('\n');
}
} // namespace jump_path_compression_ansv

int main() {
    // 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15
    // -, 0, 0,  4, 0,  2, 2,  6, 0, 1, 1,  5, 1,  3, 3,  7
    jump_path_compression_ansv::test(
        {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15});
    jump_path_compression_ansv::test({8, 4, 2});
}
