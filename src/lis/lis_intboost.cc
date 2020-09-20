// cesun, 9/19/20 9:30 PM.

/*
 * When input sequence is of type int and does not touch INT_MIN and INT_MAX,
 * lis can be further boosted by directly storing the value of the tail of lis
 * in array d[].
 */

// search [l,r)
template<typename T>
static inline int lower_bound(const T *const arr, int l, int r, const int k) {
    while (l < r) {
        int m = (l + r) >> 1; // or l+((n-l)>>1)
        if (arr[m] < k) l = m + 1;
        else r = m;
    }
    return l;
}

// when input sequence is in range [-2147483646, 2147483646]
int int_lis_luck(const int *const a, const int n) {

}

// work for all 32 bit int [-2147483648, 2147483647]
struct int_lis_long {

};
