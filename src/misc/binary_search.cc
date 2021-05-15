// cesun, 9/17/20 2:52 PM.

// precond: arr[l,r) ascending sorted

// [l,r); return in [l,r]
static inline int lower_bound(const int *const arr, int l, int r, const int k) {
    while (l < r) {
        const int m = (l + r) >> 1; // or l+((n-l)>>1)
        if (arr[m] < k)
            l = m + 1;
        else
            r = m;
    }
    return l;
}

// [l,r); return in [l,r]
static inline int upper_bound(const int *const arr, int l, int r, const int k) {
    while (l < r) {
        const int m = (l + r) >> 1; // or l+((n-l)>>1)
        if (arr[m] <= k)
            l = m + 1;
        else
            r = m;
    }
    return l;
}


// I bet it works but ... TODO: test any_bound
// search [l,r)
static inline int any_bound(const int *const arr, int l, int r, const int k) {
    while (l < r) {
        int m = (l + r) >> 1; // or l+((n-l)>>1)
        if (arr[m] < k)
            l = m + 1;
        else if (arr[m] == k)
            return m;
        else
            r = m;
    }
    return l;
}
