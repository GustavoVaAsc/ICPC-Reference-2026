// Continued fractions and Stern-Brocot search.
// cf(p,q): [a0; a1, a2, ...] of p/q. Convergents h/k: h_n = a_n h_{n-1} + h_{n-2}, same for k.
// fracBS(f, N): f monotone (false..true) on rationals; returns the fraction p/q (|p|,q <= N)
//   closest to the threshold from the side where f is true (KACTL). O(log^2 N).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> cf(ll p, ll q) {
	vector<ll> a;
	while (q) { a.push_back(p / q); ll r = p % q; p = q; q = r; }
	return a;
}
struct Frac { ll p, q; };
template <class F> Frac fracBS(F f, ll N) {
	bool dir = 1, A = 1, B = 1;
	Frac lo{0, 1}, hi{1, 0}; // Add {-1, 0} if lo < 0
	if (f(lo)) return lo;
	while (A || B) {
		ll adv = 0, step = 1; // move hi if dir, else lo
		for (int si = 0; step; (step *= 2) >>= si) {
			adv += step;
			Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
			if (abs(mid.p) > N || mid.q > N || dir == !f(mid)) { adv -= step; si = 2; }
		}
		hi.p += lo.p * adv; hi.q += lo.q * adv;
		dir = !dir; swap(lo, hi); A = B; B = !!adv;
	}
	return dir ? hi : lo;
}
// e.g. best upper approx of sqrt(2): fracBS([](Frac x){ return x.p * x.p >= 2 * x.q * x.q; }, 1000)
