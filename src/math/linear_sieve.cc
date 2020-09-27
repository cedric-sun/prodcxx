// cesun, 9/10/20 11:34 PM.
// 105097565 primes in [2,2^31-1], that's 400.92MB int array

#define MAXN 1'500'000
static bool isNotPrime[MAXN]; // thank you .bss
static int prime[MAXN / 10]; // 105097565/(1<<31) = 0.0489
static int nPrime;

void linear_sieve() {
    for (int i = 2; i < MAXN; ++i) {
        if (!isNotPrime[i]) {
            prime[nPrime++] = i;
        }
        int k;
        for (int j = 0; j < nPrime && (k = i * prime[j]) < MAXN; ++j) {
            isNotPrime[k] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
