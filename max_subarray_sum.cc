// cesun, 9/6/20 12:17 AM.

#include <algorithm>
#include <climits>

int_fast64_t max_subarray_sum(const int *const x, const int N) {
    int_fast64_t dp = 0, max = INT_FAST64_MIN;
    for (int i = 0; i < N; ++i) {
        dp = std::max(dp + x[i], static_cast<int_fast64_t>(x[i]));
        max = std::max(max, dp);
    }
    return max;
}
