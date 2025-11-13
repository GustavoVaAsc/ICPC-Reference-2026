// Binomial Coefficients with Modular Arithmetic
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;
long long fact[MAXN], inv_fact[MAXN];

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    inv_fact[MAXN-1] = mod_pow(fact[MAXN-1], MOD - 2, MOD);
    for (int i = MAXN-2; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i+1] * (i+1)) % MOD;
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (fact[n] * inv_fact[r] % MOD) * inv_fact[n-r] % MOD;
}
