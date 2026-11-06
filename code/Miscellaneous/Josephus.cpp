// Josephus problem: n people in circle, every k-th eliminated. Returns 0-indexed survivor.
// O(n); O(k log n) variant for small k; closed form for k = 2.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll josephus(ll n, ll k) { ll r = 0; for (ll i = 2; i <= n; i++) r = (r + k) % i; return r; }
ll josephusK2(ll n) { return 2 * (n - (1LL << (63 - __builtin_clzll(n)))); } // 0-indexed
ll josephusFast(ll n, ll k) { // O(k log n)
	if (n == 1) return 0;
	if (k == 1) return n - 1;
	if (k > n) return josephus(n, k);
	ll cnt = n / k, res = josephusFast(n - cnt, k);
	res -= n % k;
	if (res < 0) res += n; else res += res / (k - 1);
	return res;
}
