// Minimum enclosing circle (Welzl, iterative). Expected O(n).
#include <bits/stdc++.h>
using namespace std;
typedef long double ld; typedef complex<ld> P;
ld cross(P a, P b) { return imag(conj(a) * b); }
P circumcenter(P a, P b, P c) {
	b -= a; c -= a;
	return a + P(-b.imag() * norm(c) + c.imag() * norm(b), b.real() * norm(c) - c.real() * norm(b)) / (cross(b, c) * 2);
}
// ps must be non-empty; returns {center, radius}
pair<P, ld> mec(vector<P> ps) {
	mt19937 rng(712367);
	shuffle(ps.begin(), ps.end(), rng);
	P o = ps[0]; ld r = 0, EPS = 1 + 1e-12;
	for (size_t i = 0; i < ps.size(); i++) if (abs(o - ps[i]) > r * EPS) {
		o = ps[i]; r = 0;
		for (size_t j = 0; j < i; j++) if (abs(o - ps[j]) > r * EPS) {
			o = (ps[i] + ps[j]) / (ld)2; r = abs(o - ps[i]);
			for (size_t k = 0; k < j; k++) if (abs(o - ps[k]) > r * EPS) {
				o = circumcenter(ps[i], ps[j], ps[k]); r = abs(o - ps[i]);
			}
		}
	}
	return {o, r};
}
