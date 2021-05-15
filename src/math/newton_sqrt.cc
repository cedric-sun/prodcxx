#include <bits/stdc++.h>
using namespace std;

// newton's method for square root

double newton(const double a, const double eps = 1e-6) {
    double z0 = 1, z1;
    int cnt = 0;
    while (true) {
        ++cnt;
        z1 = (z0 * z0 + a) / (2 * z0);
        if (abs(z0 - z1) < eps)
            break;
        z0 = z1;
    }
    printf("sqrt of %f = %f,precision = %f, in %d iterations\n", a, z1, eps,
           cnt);
    return z1;
}

int main() {
    double a;
    while (cin >> a) {
        newton(a);
    }
    return 0;
}
