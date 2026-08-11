// Linear Recurrence solver using Berlekamp-Massey + Kitamasa
// O(k^3 log n) where k is the recurrence order
// Mod 1e9+7

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1e9 + 7;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

// Berlekamp-Massey: find minimal linear recurrence relation
// Returns coefficients c where sequence s satisfies:
// s[n] = c[0]*s[n-1] + c[1]*s[n-2] + ... + c[k-1]*s[n-k]
vector<ll> berlekampMassey(const vector<ll> &s) {
    vector<ll> c, oldC;
    int f = -1;
    for (int i = 0; i < (int)s.size(); i++) {
        ll delta = s[i] % MOD;
        for (int j = 1; j <= (int)c.size(); j++) {
            delta = (delta - c[j - 1] * s[i - j]) % MOD;
        }
        if (delta == 0) continue;
        if (f == -1) {
            c.assign(i + 1, 0);
            c[i] = 1;
            f = i;
        } else {
            vector<ll> d = oldC;
            for (ll &x : d) x = (MOD - x) % MOD;
            d.insert(d.begin(), 1);
            ll df1 = 0;
            for (int j = 1; j <= (int)d.size(); j++) {
                df1 = (df1 + d[j - 1] * s[f + 1 - j]) % MOD;
            }
            ll coef = delta * modpow(df1, MOD - 2) % MOD;
            for (ll &x : d) x = x * coef % MOD;
            d.insert(d.end(), i - f - 1, 0);
            vector<ll> temp = c;
            c.resize(max(c.size(), d.size()));
            for (int j = 0; j < (int)d.size(); j++)
                c[j] = (c[j] + d[j]) % MOD;
            if (i - (int)temp.size() > f - (int)oldC.size()) {
                oldC = temp;
                f = i;
            }
        }
    }
    // Normalize: leading coefficient should be 1
    if (!c.empty() && c.back() != 1) {
        ll inv = modpow(c.back(), MOD - 2);
        for (ll &x : c) x = x * inv % MOD;
    }
    return c;
}

// Kitamasa: combine two polynomials modulo the recurrence relation
vector<ll> combine(const vector<ll> &a, const vector<ll> &b, const vector<ll> &trans) {
    int k = trans.size();
    vector<ll> res(2 * k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
        }
    }
    // Reduce degree >= k terms using the recurrence
    for (int i = 2 * k - 1; i >= k; i--) {
        for (int j = 1; j <= k; j++) {
            res[i - j] = (res[i - j] + res[i] * trans[j - 1]) % MOD;
        }
    }
    res.resize(k);
    return res;
}

// Kitamasa: compute coefficients for a^n
vector<ll> kitamasa(ll n, const vector<ll> &trans) {
    int k = trans.size();
    vector<ll> res(k), coef(k);
    res[0] = 1;
    coef[1 % k] = 1;  // Kitamasa(1) in the semiring: [0, 1, 0, ...]
    while (n > 0) {
        if (n & 1) res = combine(res, coef, trans);
        coef = combine(coef, coef, trans);
        n >>= 1;
    }
    return res;
}

// Compute the n-th term of a linear recurrence
// init: first k terms of the sequence
// trans: recurrence coefficients [c0, c1, ..., c_{k-1}]
//        meaning s[n] = c0*s[n-1] + c1*s[n-2] + ... + c_{k-1}*s[n-k]
ll linear_recurrence(vector<ll> init, vector<ll> trans, ll n) {
    int k = trans.size();
    if (k == 0) return 0;
    if (n < (ll)init.size()) return init[n] % MOD;
    vector<ll> coef = kitamasa(n, trans);
    ll res = 0;
    for (int i = 0; i < k; i++) {
        res = (res + coef[i] * init[i]) % MOD;
    }
    return res;
}
