// Modular square root (Tonelli-Shanks), p odd prime. Returns x with x^2 = a (mod p), or -1 if none.
// The other root is p - x. O(log^2 p).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll pw(ll b, ll e, ll m) { ll r = 1; for (b %= m; e; e >>= 1, b = (__int128)b * b % m) if (e & 1) r = (__int128)r * b % m; return r; }
ll sqrtMod(ll a, ll p) {
	a %= p;
	if (a == 0) return 0;
	if (pw(a, (p - 1) / 2, p) != 1) return -1;
	if (p % 4 == 3) return pw(a, (p + 1) / 4, p);
	ll s = p - 1; int r = 0;
	while (s % 2 == 0) s /= 2, r++;
	ll n = 2;
	while (pw(n, (p - 1) / 2, p) != p - 1) n++;
	ll x = pw(a, (s + 1) / 2, p), b = pw(a, s, p), g = pw(n, s, p);
	for (;;) {
		ll t = b; int m = 0;
		for (; m < r && t != 1; m++) t = (__int128)t * t % p;
		if (m == 0) return x;
		ll gs = pw(g, 1LL << (r - m - 1), p);
		g = (__int128)gs * gs % p; x = (__int128)x * gs % p; b = (__int128)b * g % p; r = m;
	}
}
