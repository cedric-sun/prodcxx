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


#include <cstdio>

int main() {

}