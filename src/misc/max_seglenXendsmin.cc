// cesun, 9/20/20 1:17 PM.

// for int a[n] whose elements >=0
// maximize (j-i)*min(a[i],a[j]) over i,j : 0<=i<j<n

static int max_seglen_x_endsmin(const int *const a, const int n) {
    int max = 0;
    int prod;
    for (int l = 0, r = n - 1; l < r;) {
        if (a[l] < a[r]) {
            prod = a[l] * (r - l);
            l++;
        } else {
            prod = a[r] * (r - l);
            r--;
        }
        if (max < prod) max = prod;
    }
    return max;
}