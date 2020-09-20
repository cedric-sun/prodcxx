// cesun, 9/8/20 6:22 PM.

#include <cstdint>

// 月  球  魔  术  ，  要  开  始  了  噢  ！

// UB when x<=1
static inline uint64_t ceil_log2(uint64_t x) {
    return 64U - __builtin_clzl(x - 1);
}

// UB when x=0
static inline uint64_t floor_log2(uint64_t x) {
    return 63U - __builtin_clzl(x);
}

// fast a*b % n
int_fast64_t modmul(int_fast64_t a, int_fast64_t b, int_fast64_t n) {
    int_fast64_t ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % n;
        a = (a + a) % n;
        b >>= 1;
    }
    return ans;
}

int_fast64_t modexp(int_fast64_t a, int_fast64_t b, int_fast64_t n) {
    int_fast64_t ans = 1;
    while (b) {
        if (b & 1) ans = modmul(ans, a, n);
        a = modmul(a, a, n);
        b >>= 1;
    }
    return ans;
}
