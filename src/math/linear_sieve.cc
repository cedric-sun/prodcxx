// cesun, 9/10/20 11:34 PM.
// 105097565 primes in [2,2^31-1], that's 400.92MB int array

constexpr int MAXN = 50; // upper bound of our search
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
                // Since we iterative prime[] in ascending order, prime[j] is the smallest prime factor of i.
                // We stop going further in prime[].
                // This is the key of being a linear sieve: don't be too hard-working.

                // Proof:
                // denote b = i / prime[j], i.e. i=prime[j]*b
                // If we know prime[j] is the smallest prime factor of i and DO NOT STOP HERE,
                // in the next iteration we will mark i*(prime[j+1]) = prime[j] * prime[j+1] * b as non-prime.
                // But this number will be marked non-prime again when later i grows to prime[j+1] * b.
                break;
            }
        }
    }
}

int main() {
    linear_sieve();
}
