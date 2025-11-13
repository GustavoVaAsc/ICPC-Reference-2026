// Modular Exponentiation
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Modular Inverse using Fermat's Little Theorem
// Works when mod is prime
long long mod_inv(long long a, long long mod) {
    return mod_pow(a, mod - 2, mod);
}
