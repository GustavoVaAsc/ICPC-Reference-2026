#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Extended GCD returning gcd and setting x, y such that ax + by = gcd(a, b)
ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Chinese Remainder Theorem
// Given x == a[i] (mod m[i]) for pairwise coprime m[i], returns (x_mod, lcm)
// where x is the unique solution modulo lcm = product of m[i]
pair<ll, ll> crt(const vector<ll>& a, const vector<ll>& m) {
    ll x = 0;
    ll M = 1;

    for (size_t i = 0; i < a.size(); i++) {
        ll ai = ((a[i] % m[i]) + m[i]) % m[i];
        ll mi = m[i];

        // Solve: M * t == (ai - x) (mod mi)
        ll diff = (ai - x) % mi;
        if (diff < 0) diff += mi;

        ll t, y;
        ll g = extgcd(M, mi, t, y);
        // M and mi are coprime, so g == 1
        t = (t % mi + mi) % mi;
        t = (__int128)t * diff % mi;

        x = x + (__int128)M * t;
        M = (__int128)M * mi / g;

        x %= M;
        if (x < 0) x += M;
    }

    return {x, M};
}