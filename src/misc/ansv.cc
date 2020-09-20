// cesun, 9/14/20 1:33 AM.

// https://en.wikipedia.org/wiki/All_nearest_smaller_values

#include <vector>

using std::vector;

// the 0-th element of the return value makes no sense
// return P[x.size()] such that x[P[i]] < x[i], and i-P[i] is minimal
vector<int> ansv(const vector<int> &x) {
    vector<int> ans(x.size());
    for (int i = 0; i < x.size(); ++i) {
        int j = i - 1;
        while (j >= 0 && x[j] >= x[i])
            j = ans[j];
        ans[i] = j;
    }
    return ans;
}


// 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15
// -, 0, 0,  4, 0,  2, 2,  6, 0, 1, 1,  5, 1,  3, 3,  7
#include <cstdio>

int main() {
    vector<int> data{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    for (int i : ansv(data)) {
        if (i >= 0)
            printf("%d ", data[i]);
        else
            fputs("- ", stdout);
    }
    putchar('\n');
}
