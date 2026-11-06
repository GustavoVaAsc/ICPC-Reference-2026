// Pick's theorem: A = I + B/2 - 1  (I interior lattice pts, B boundary pts; B = sum gcd(|dx|,|dy|) over edges).
//   I = A - B/2 + 1, so with A2 = 2*area: I = (A2 - B + 2) / 2.
// Triangle ABC, a=|BC|, b=|CA|, c=|AB|:
//   incenter = (a*A + b*B + c*C) / (a+b+c), inradius = area / s (s = semiperimeter)
//   circumradius R = abc / (4*area); circumcenter below.
#include <bits/stdc++.h>
using namespace std;
typedef long double ld; typedef complex<ld> P;
ld cross(P a, P b) { return imag(conj(a) * b); }
P circumcenter(P a, P b, P c) {
	b -= a; c -= a;
	return a + P(-b.imag() * norm(c) + c.imag() * norm(b), b.real() * norm(c) - c.real() * norm(b)) / (cross(b, c) * 2);
}
P incenter(P A, P B, P C) {
	ld a = abs(B - C), b = abs(C - A), c = abs(A - B);
	return (A * a + B * b + C * c) / (a + b + c);
}
long long pickInterior(const vector<pair<long long, long long>> &p) { // simple polygon
	long long A2 = 0, B = 0; int n = p.size();
	for (int i = 0; i < n; i++) {
		auto [x1, y1] = p[i]; auto [x2, y2] = p[(i + 1) % n];
		A2 += x1 * y2 - x2 * y1;
		B += __gcd(llabs(x2 - x1), llabs(y2 - y1));
	}
	return (llabs(A2) - B + 2) / 2;
}
