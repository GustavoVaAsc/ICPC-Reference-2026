void precompute(ll n = MAXN - 1) {
    factorial[0] = factorial[1] = 1;
    
    // Compute factorials
    for (ll i = 2; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    
    // Compute inverse factorials efficiently
    inv_factorial[n] = modInv(factorial[n]);
    for (ll i = n - 1; i >= 0; i--) {
        inv_factorial[i] = 
            (inv_factorial[i + 1] * (i + 1)) % MOD;
    }
}