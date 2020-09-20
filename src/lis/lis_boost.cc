// cesun, 9/13/20 2:44 AM.

/*
 * Lis boosted by minimizing the times of binary search.
 * Requires overload of both < and ==
 * TODO: use only < and ==
 */

template<typename T>
struct lis {
    // [0,r)
    static inline int lower_bound(const T *const a, const int *const d, int r, const T &key) {
        int l = 0;
        while (l < r) {
            int m = (l + r) >> 1; // or l+((n-l)>>1)
            if (a[d[m]] < key) l = m + 1;
            else r = m;
        }
        return l;
    }

    //precond: n>0
    static int work(const T *const a, const int n) {
        int *d = new int[n]; // a[d[i]] is the value of tail of lis of size i+1
        d[0] = 0; // init: lis of size 1 end at a[0]
        int dsz = 1;
        for (int i = 1; i < n; ++i) {
            if (a[i] <= a[d[0]])
                d[0] = i;
            else if (a[i] > a[d[dsz - 1]])
                d[dsz++] = i;
            else if (a[i] == a[d[dsz - 1]])
                d[dsz - 1] = i;
            else
                d[lower_bound(a, d, dsz, a[i])] = i;
        }
        delete[] d;
        return dsz;
    }
};