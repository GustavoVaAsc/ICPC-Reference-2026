// Lucy_Hedgehog: pi(n) and sum of primes <= n in O(n^(3/4)) (n up to ~1e11). Same idea as Min_25 sieve part 1.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// returns {pi(n), sum of primes <= n}
pair<ll, ll> lucy(ll n) {
	ll r = sqrtl(n);
	while (r * r > n) r--;
	while ((r + 1) * (r + 1) <= n) r++;
	vector<ll> cl(r + 2), cs(r + 2), gl(r + 2), gs(r + 2); // small: v=i, large: v=n/i
	auto tri = [](ll v) { return (__int128)v * (v + 1) / 2; };
	for (ll i = 1; i <= r; i++) {
		cl[i] = i - 1; cs[i] = tri(i) - 1;
		ll v = n / i; gl[i] = v - 1; gs[i] = tri(v) - 1;
	}
	for (ll p = 2; p <= r; p++) {
		if (cl[p] == cl[p - 1]) continue;
		ll pc = cl[p - 1], ps = cs[p - 1], p2 = p * p;
		for (ll i = 1; i <= min(r, n / p2); i++) {
			ll d = i * p; // n/i/p = n/d
			ll c, s;
			if (d <= r) c = gl[d], s = gs[d]; else c = cl[n / d], s = cs[n / d];
			gl[i] -= c - pc; gs[i] -= p * (s - ps);
		}
		for (ll v = r; v >= p2; v--) cl[v] -= cl[v / p] - pc, cs[v] -= p * (cs[v / p] - ps);
	}
	if (n < 2) return {0, 0};
	return {gl[1], gs[1]};
}
