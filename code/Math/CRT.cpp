using ll = long long;
using i128 = __int128_t;

// Chinese Remainder Theorem (CRT), supports non-coprime moduli.
// Main use cases:
// 1) Reconstruct x from multiple congruences x = r_i (mod m_i).
// 2) Merge answers from different moduli after number-theory computations.
// 3) Works even when moduli are not coprime; detects inconsistency.

ll extGcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Returns {r, m} meaning x = r (mod m). If no solution, returns {0, -1}.
pair<ll, ll> crtMerge(pair<ll, ll> A, pair<ll, ll> B) {
    ll r1 = A.first, m1 = A.second;
    ll r2 = B.first, m2 = B.second;

    ll p, q;
    ll g = extGcd(m1, m2, p, q);

    if ((r2 - r1) % g != 0) return {0, -1};

    ll lcm = m1 / g * m2;
    i128 t = (i128)(r2 - r1) / g * p;
    ll mod = m2 / g;
    ll k = (ll)((t % mod + mod) % mod);

    i128 ans = (i128)r1 + (i128)k * m1;
    ll r = (ll)((ans % lcm + lcm) % lcm);
    return {r, lcm};
}

pair<ll, ll> crt(const vector<ll> &r, const vector<ll> &m) {
    pair<ll, ll> cur = {0, 1};
    for (int i = 0; i < (int)r.size(); i++) {
        cur = crtMerge(cur, {((r[i] % m[i]) + m[i]) % m[i], m[i]});
        if (cur.second == -1) return cur;
    }
    return cur;
}

// Example of use:
// x = 2 (mod 6), x = 5 (mod 9)
// vector<ll> r = {2, 5}, m = {6, 9};
// auto [x, mod] = crt(r, m);
// if (mod == -1) -> no solution
// else all solutions are x + k*mod
