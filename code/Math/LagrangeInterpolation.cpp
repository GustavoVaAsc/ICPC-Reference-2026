// Lagrange interpolation mod prime.
// lagrangeConsecutive: f given at 0..n-1 (deg < n), evaluate at x in O(n).
// lagrangeGeneral: arbitrary distinct xs, O(n^2).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
ll pw(ll b, ll e) { ll r = 1; for (b %= MOD; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD; return r; }
ll lagrangeConsecutive(const vector<ll> &y, ll x) {
	int n = y.size(); x %= MOD;
	if (x < n) return y[x];
	vector<ll> pre(n + 1, 1), suf(n + 1, 1), fact(n, 1), ifact(n, 1);
	for (int i = 1; i < n; i++) fact[i] = fact[i - 1] * i % MOD;
	ifact[n - 1] = pw(fact[n - 1], MOD - 2);
	for (int i = n - 1; i > 0; i--) ifact[i - 1] = ifact[i] * i % MOD;
	for (int i = 0; i < n; i++) pre[i + 1] = pre[i] * ((x - i + MOD) % MOD) % MOD;
	for (int i = n - 1; i >= 0; i--) suf[i] = suf[i + 1] * ((x - i + MOD) % MOD) % MOD;
	ll res = 0;
	for (int i = 0; i < n; i++) {
		ll t = y[i] % MOD * pre[i] % MOD * suf[i + 1] % MOD * ifact[i] % MOD * ifact[n - 1 - i] % MOD;
		res = (res + ((n - 1 - i) & 1 ? MOD - t : t)) % MOD;
	}
	return res % MOD;
}
ll lagrangeGeneral(const vector<ll> &xs, const vector<ll> &ys, ll x) {
	int n = xs.size(); ll res = 0;
	for (int i = 0; i < n; i++) {
		ll num = 1, den = 1;
		for (int j = 0; j < n; j++) if (j != i) {
			num = num * ((x - xs[j]) % MOD + MOD) % MOD;
			den = den * ((xs[i] - xs[j]) % MOD + MOD) % MOD;
		}
		res = (res + ys[i] % MOD * num % MOD * pw(den, MOD - 2)) % MOD;
	}
	return res;
}
