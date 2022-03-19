// cesun, 9/8/20 6:22 PM.

#include <cstdint>
#include <vector>

using namespace std;

/**
 * @brief ceil(log2(x))
 * 
 * Undefined behavior when x<=1.
 * 
 * @param x 
 * @return uint64_t 
 */
uint64_t ceil_log2(uint64_t x)
{
    return 64U - __builtin_clzl(x - 1);
}

/**
 * @brief floor(log2(x))
 * 
 * Undefined behavior when x=0.
 * 
 * @param x 
 * @return uint64_t 
 */
uint64_t floor_log2(uint64_t x)
{
    return 63U - __builtin_clzl(x);
}

/**
 * @brief 预计算 ans[i] = floor(log2(i)); i in [0,n]
 */
vector<int> compute_floor_log2(const int n) {
    vector<int> ans(n + 1);
    ans[1] = 0;
    for (int i = 2; i <= n; i++)
        ans[i] = ans[i >> 1] + 1;
    return ans;
}