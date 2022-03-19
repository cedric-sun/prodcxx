#include <cstdint>

/**
 * @brief Binary implementation computing a*b % n
 * 
 * @param a 
 * @param b 
 * @param n 
 * @return int_fast64_t 
 */
int_fast64_t modmul(int_fast64_t a, int_fast64_t b, int_fast64_t n) {
    int_fast64_t ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % n;
        a = (a + a) % n;
        b >>= 1;
    }
    return ans;
}

/**
 * @brief Binary implementation computing a^b % n
 * 
 * @param a 
 * @param b 
 * @param n 
 * @return int_fast64_t 
 */
int_fast64_t modexp(int_fast64_t a, int_fast64_t b, int_fast64_t n) {
    int_fast64_t ans = 1;
    while (b) {
        if (b & 1) ans = modmul(ans, a, n);
        a = modmul(a, a, n);
        b >>= 1;
    }
    return ans;
}
