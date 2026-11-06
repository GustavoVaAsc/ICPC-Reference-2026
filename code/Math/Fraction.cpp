// Rational number struct (normalized, den > 0). Comparison via __int128.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Frac {
	ll p, q;
	Frac(ll p = 0, ll q = 1) : p(p), q(q) {
		if (q < 0) this->p = -p, this->q = -q;
		ll g = __gcd(llabs(this->p), this->q);
		if (g > 1) this->p /= g, this->q /= g;
	}
	Frac operator+(Frac o) const { return Frac(p * o.q + o.p * q, q * o.q); }
	Frac operator-(Frac o) const { return Frac(p * o.q - o.p * q, q * o.q); }
	Frac operator*(Frac o) const { return Frac(p * o.p, q * o.q); }
	Frac operator/(Frac o) const { return Frac(p * o.q, q * o.p); }
	bool operator<(Frac o) const { return (__int128)p * o.q < (__int128)o.p * q; }
	bool operator==(Frac o) const { return p == o.p && q == o.q; }
};
