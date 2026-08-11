// Garner's Algorithm for Chinese Remainder Theorem with non-coprime moduli
// Solves x == a_i (mod m_i) for arbitrary moduli
// Returns x mod lcm(m_i), or -1 if no solution

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Extended modular inverse that works for non-coprime case
// Returns inverse of a modulo mod, or -1 if doesn't exist
// When gcd(a, mod) = d > 1, the inverse of (a/d) modulo (mod/d) is returned
// and the gcd is returned in g
ll modInvExt(ll a, ll mod, ll &g) {
    ll x, y;
    g = egcd(a, mod, x, y);
    if (g != 1) return -1;
    return (x % mod + mod) % mod;
}

// Check if system x == a[i] (mod m[i]) is consistent
bool checkConsistency(const vector<ll> &a, const vector<ll> &m) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll g = std::gcd(m[i], m[j]);
            if ((a[j] - a[i]) % g != 0) return false;
        }
    }
    return true;
}

// Compute lcm of all moduli
ll lcmAll(const vector<ll> &m) {
    ll res = 1;
    for (ll mod : m) {
        res = std::lcm(res, mod);
    }
    return res;
}

// Garner's algorithm for arbitrary (not necessarily coprime) moduli
// Returns solution x mod lcm(m_i), or -1 if no solution exists
// Uses Garner's recurrence with precomputed inverses for coprime components
ll garner(const vector<ll> &a, const vector<ll> &m) {
    int n = a.size();
    if (n == 0) return 0;

    // Check consistency of the system
    if (!checkConsistency(a, m)) return -1;

    // Build solution iteratively using Garner's recurrence
    // At step i: we have cur satisfying congruences 0..i-1
    // We want to find t such that: cur + Q * t == a[i] (mod m[i])
    // where Q = lcm(m[0], ..., m[i-1])
    //
    // This is equivalent to Q * t == (a[i] - cur) (mod m[i])
    // Let d = gcd(Q, m[i]). For solution to exist, d | (a[i] - cur)
    // Then: (Q/d) * t == (a[i] - cur)/d (mod m[i]/d)
    // Since gcd(Q/d, m[i]/d) = 1, we can find inverse

    ll cur = a[0] % m[0];
    if (cur < 0) cur += m[0];
    ll Q = m[0];  // lcm of processed moduli

    for (int i = 1; i < n; i++) {
        ll diff = a[i] - cur;
        ll mi = m[i];

        // d = gcd(Q, mi)
        ll d = std::gcd(Q, mi);

        // Check divisibility: solution exists iff d | diff
        if (diff % d != 0) return -1;  // Should not happen if consistency check passed

        // Reduce: (Q/d) * t == (diff/d) (mod mi/d)
        ll Qd = Q / d;
        ll mid = mi / d;
        ll diffd = diff / d;

        // Find inverse of Qd modulo mid
        ll inv, g;
        inv = modInvExt(Qd % mid, mid, g);
        if (inv == -1) return -1;  // Should not happen

        // t = (diffd * inv) mod mid
        ll t = (diffd % mid * inv) % mid;
        if (t < 0) t += mid;

        // Update cur and Q
        cur = cur + Q * t;
        Q = std::lcm(Q, mi);

        // Normalize cur to be within [0, Q)
        cur %= Q;
        if (cur < 0) cur += Q;
    }

    return cur % lcmAll(m);
}
