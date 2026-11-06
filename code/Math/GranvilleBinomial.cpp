// nCk mod p^e (Granville). Query O(p^e) precompute + O(log n * log) per query.
// For general modulus: factor, call per prime power, combine with CRT.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct PrimePowBinom {
	ll p, e, pe; vector<ll> f; // f[i] = i! with factors of p removed, mod p^e
	ll pw(ll b, ll x) { ll r = 1; for (b %= pe; x; x >>= 1, b = b * b % pe) if (x & 1) r = r * b % pe; return r; }
	ll inv(ll a) { // a coprime with p; extended Euclid
		ll g = pe, x = 0, y = 1, b = a % pe, m = pe;
		while (b) { ll q = m / b; tie(m, b) = make_pair(b, m - q * b); tie(x, y) = make_pair(y, x - q * y); }
		return (x % pe + pe) % pe;
	}
	PrimePowBinom(ll p, ll e) : p(p), e(e), pe(1) {
		for (int i = 0; i < e; i++) pe *= p;
		f.assign(pe, 1);
		for (ll i = 1; i < pe; i++) f[i] = f[i - 1] * (i % p ? i : 1) % pe;
	}
	ll fact(ll n) { return n == 0 ? 1 : pw(f[pe - 1], n / pe) * f[n % pe] % pe * fact(n / p) % pe; }
	ll vp(ll n) { ll r = 0; while (n) n /= p, r += n; return r; }
	ll C(ll n, ll k) {
		if (k < 0 || k > n) return 0;
		ll v = vp(n) - vp(k) - vp(n - k);
		if (v >= e) return 0;
		ll r = fact(n) * inv(fact(k) * fact(n - k) % pe) % pe;
		while (v--) r = r * p % pe;
		return r;
	}
};
