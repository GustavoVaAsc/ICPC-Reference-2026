// Lucas: nCk mod small prime p (p <= ~1e6). Precompute O(p), query O(log_p n).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Lucas {
	ll p; vector<ll> f, inv;
	ll pw(ll b, ll e) { ll r = 1; for (b %= p; e; e >>= 1, b = b * b % p) if (e & 1) r = r * b % p; return r; }
	Lucas(ll p) : p(p), f(p), inv(p) {
		f[0] = 1;
		for (ll i = 1; i < p; i++) f[i] = f[i - 1] * i % p;
		for (ll i = 0; i < p; i++) inv[i] = pw(f[i], p - 2);
	}
	ll small(ll n, ll k) { return k > n ? 0 : f[n] * inv[k] % p * inv[n - k] % p; }
	ll C(ll n, ll k) {
		ll r = 1;
		for (; n || k; n /= p, k /= p) r = r * small(n % p, k % p) % p;
		return r;
	}
};
