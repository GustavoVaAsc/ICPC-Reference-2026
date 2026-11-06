using u64 = uint64_t;
using u128 = __uint128_t;

// Pollard Rho factorization + Miller Rabin primality (64-bit)
// Main use cases:
// 1) Fast factorization for numbers up to 1e18.
// 2) Problems asking prime decomposition of large semiprimes.
// 3) Number theory tasks needing divisors / phi from large n.

u64 modMul(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 modPow(u64 a, u64 e, u64 mod) {
    u64 r = 1;
    while (e) {
        if (e & 1) r = modMul(r, a, mod);
        a = modMul(a, a, mod);
        e >>= 1;
    }
    return r;
}

bool isPrime64(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }

    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    // Deterministic bases for 64-bit integers.
    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        u64 x = modPow(a % n, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (u64 r = 1; r < s; r++) {
            x = modMul(x, x, n);
            if (x == n - 1) {
                comp = false;
                break;
            }
        }
        if (comp) return false;
    }
    return true;
}

u64 pollardRho(u64 n) {
    if ((n & 1ULL) == 0) return 2;

    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<u64> dist(2, n - 2);

    while (true) {
        u64 c = dist(rng);
        u64 x = dist(rng);
        u64 y = x;
        u64 d = 1;

        auto f = [&](u64 v) {
            return (modMul(v, v, n) + c) % n;
        };

        while (d == 1) {
            x = f(x);
            y = f(f(y));
            u64 diff = (x > y ? x - y : y - x);
            d = gcd(diff, n);
        }

        if (d != n) return d;
    }
}

void factorRec(u64 n, map<u64, int>& fac) {
    if (n == 1) return;
    if (isPrime64(n)) {
        fac[n]++;
        return;
    }
    u64 d = pollardRho(n);
    factorRec(d, fac);
    factorRec(n / d, fac);
}

map<u64, int> factorize64(u64 n) {
    map<u64, int> fac;
    factorRec(n, fac);
    return fac;
}

// Example of use:
// u64 n; cin >> n;
// auto fac = factorize64(n);
// for (auto [p, e] : fac) cout << p << "^" << e << " ";

// Contest note:
// For many test cases with small numbers, trial division can still be faster.
