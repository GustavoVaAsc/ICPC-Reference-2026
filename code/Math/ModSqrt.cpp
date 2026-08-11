// Returns one x such that x^2 == a (mod p), where p is prime.
// The other root is p - x. Returns -1 if no square root exists.

typedef long long ll;

static ll mod_pow(ll a, ll e, ll mod) {
    ll r = 1;
    a %= mod;
    while (e > 0) {
        if (e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}

ll mod_sqrt(ll a, ll p) {
    a %= p;
    if (a < 0) a += p;

    if (a == 0) return 0;
    if (p == 2) return a;

    // Legendre symbol: a^((p-1)/2) mod p == 1  -> quadratic residue
    //                                      == p-1 -> non-residue
    if (mod_pow(a, (p - 1) / 2, p) != 1) return -1;

    // p == 3 (mod 4): simple closed form
    if (p % 4 == 3) return mod_pow(a, (p + 1) / 4, p);

    // p == 1 (mod 4): Tonelli-Shanks
    // Factor p-1 = q * 2^s with q odd
    ll q = p - 1;
    int s = 0;
    while ((q & 1) == 0) {
        q >>= 1;
        ++s;
    }

    // Find a quadratic non-residue z
    ll z = 2;
    while (mod_pow(z, (p - 1) / 2, p) != p - 1) ++z;

    ll c = mod_pow(z, q, p);          // c = z^q mod p
    ll x = mod_pow(a, (q + 1) / 2, p); // x = a^{(q+1)/2} mod p
    ll t = mod_pow(a, q, p);          // t = a^q mod p
    int m = s;

    for (int i = 1; i < m; ++i) {
        ll tp = t;
        int d = 1;
        while (d < m - i) {
            tp = tp * tp % p;
            d <<= 1;
        }
        if (tp != 1) {
            x = x * mod_pow(c, 1 << (m - i - 1), p) % p;
            c = c * c % p;
            t = t * c % p;
        }
    }

    return x;
}
