// Polynomial toolkit mod 998244353: mul, inv, log, exp, sqrt, divmod. All O(n log n).
// log/sqrt need a[0] = 1, exp needs a[0] = 0, inv needs a[0] != 0. Results truncated to n terms.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef vector<ll> poly;
const ll MOD = 998244353;
ll pw(ll b, ll e) { ll r = 1; for (b %= MOD; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD; return r; }
void ntt(poly &a, bool inv) {
	int n = a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		ll w = pw(3, (MOD - 1) / len);
		if (inv) w = pw(w, MOD - 2);
		for (int i = 0; i < n; i += len) {
			ll wn = 1;
			for (int j = 0; j < len / 2; j++, wn = wn * w % MOD) {
				ll u = a[i + j], v = a[i + j + len / 2] * wn % MOD;
				a[i + j] = (u + v) % MOD; a[i + j + len / 2] = (u - v + MOD) % MOD;
			}
		}
	}
	if (inv) { ll ni = pw(n, MOD - 2); for (ll &x : a) x = x * ni % MOD; }
}
poly mul(poly a, poly b, int lim = -1) { // product truncated to lim terms
	int need = a.size() + b.size() - 1, n = 1;
	while (n < need) n <<= 1;
	a.resize(n); b.resize(n); ntt(a, 0); ntt(b, 0);
	for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
	ntt(a, 1); a.resize(lim < 0 ? need : lim);
	return a;
}
poly trunc(const poly &a, int n) { poly r(a.begin(), a.begin() + min((int)a.size(), n)); r.resize(n); return r; }
poly inv(const poly &a, int n) {
	poly b = {pw(a[0], MOD - 2)};
	for (int len = 1; len < n; len <<= 1) {
		poly t = mul(trunc(a, 2 * len), b, 2 * len);
		for (ll &x : t) x = (MOD - x) % MOD;
		t[0] = (t[0] + 2) % MOD;
		b = mul(b, t, 2 * len);
	}
	b.resize(n); return b;
}
poly deriv(const poly &a) { poly r; for (size_t i = 1; i < a.size(); i++) r.push_back(a[i] * i % MOD); return r; }
poly integ(const poly &a) { poly r(a.size() + 1); for (size_t i = 0; i < a.size(); i++) r[i + 1] = a[i] * pw(i + 1, MOD - 2) % MOD; return r; }
poly log(const poly &a, int n) { poly r = integ(mul(deriv(a), inv(a, n), n)); r.resize(n); return r; }
poly exp(const poly &a, int n) {
	poly b = {1};
	for (int len = 1; len < n; len <<= 1) {
		poly lg = log(b, 2 * len), t = trunc(a, 2 * len);
		for (int i = 0; i < 2 * len; i++) t[i] = (t[i] - (i < (int)lg.size() ? lg[i] : 0) + MOD) % MOD;
		t[0] = (t[0] + 1) % MOD;
		b = mul(b, t, 2 * len);
	}
	b.resize(n); return b;
}
poly sqrt(const poly &a, int n) { // a[0] = 1
	poly b = {1}; ll i2 = pw(2, MOD - 2);
	for (int len = 1; len < n; len <<= 1) {
		poly t = mul(inv(b, 2 * len), trunc(a, 2 * len), 2 * len);
		b.resize(2 * len);
		for (int i = 0; i < 2 * len; i++) b[i] = (b[i] + t[i]) % MOD * i2 % MOD;
	}
	b.resize(n); return b;
}
pair<poly, poly> divmod(poly a, poly b) { // a = q*b + r
	int n = a.size(), m = b.size();
	if (n < m) return {{0}, a};
	poly ra(a.rbegin(), a.rend()), rb(b.rbegin(), b.rend());
	poly q = mul(trunc(ra, n - m + 1), inv(rb, n - m + 1), n - m + 1);
	reverse(q.begin(), q.end());
	poly qb = mul(q, b), r(m - 1);
	for (int i = 0; i < m - 1; i++) r[i] = (a[i] - qb[i] + MOD) % MOD;
	return {q, r};
}
