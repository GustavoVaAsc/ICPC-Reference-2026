// Primitive root modulo prime p (smallest), O(sqrt p + log^2 p). Exists for n = 1,2,4,p^k,2p^k.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll pw(ll b, ll e, ll m) { ll r = 1; for (b %= m; e; e >>= 1, b = (__int128)b * b % m) if (e & 1) r = (__int128)r * b % m; return r; }
ll primitiveRoot(ll p) {
	if (p == 2) return 1;
	vector<ll> f; ll x = p - 1;
	for (ll i = 2; i * i <= x; i++) if (x % i == 0) { f.push_back(i); while (x % i == 0) x /= i; }
	if (x > 1) f.push_back(x);
	for (ll g = 2;; g++) {
		bool ok = true;
		for (ll q : f) if (pw(g, (p - 1) / q, p) == 1) { ok = false; break; }
		if (ok) return g;
	}
}
