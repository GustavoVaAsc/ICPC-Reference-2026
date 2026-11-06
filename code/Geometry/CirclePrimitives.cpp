// Circle primitives (complex<ld>). Circle = (center c, radius r).
#include <bits/stdc++.h>
using namespace std;
typedef long double ld; typedef complex<ld> P;
ld cross(P a, P b) { return imag(conj(a) * b); }
ld dot(P a, P b) { return real(conj(a) * b); }
const ld EPS = 1e-12;
P perp(P a) { return P(-a.imag(), a.real()); }
// Circle-line (line through a,b): 0, 1 or 2 points
vector<P> circleLine(P c, ld r, P a, P b) {
	P d = b - a, h = a + d * (dot(c - a, d) / norm(d));
	ld h2 = r * r - norm(h - c);
	if (h2 < -EPS) return {};
	P s = d * (sqrtl(max(h2, (ld)0)) / abs(d));
	if (h2 <= EPS) return {h};
	return {h + s, h - s};
}
// Circle-circle: 0, 1 or 2 points (same circle -> empty)
vector<P> circleCircle(P a, ld r1, P b, ld r2) {
	if (a == b) return {};
	P v = b - a;
	ld d2 = norm(v), s = r1 + r2, df = r1 - r2;
	ld p = (d2 + r1 * r1 - r2 * r2) / (d2 * 2), h2 = r1 * r1 - p * p * d2;
	if (s * s < d2 - EPS || df * df > d2 + EPS) return {};
	P mid = a + v * p, per = perp(v) * sqrtl(max(h2, (ld)0) / d2);
	if (h2 <= 0) return {mid};
	return {mid + per, mid - per};
}
// Tangent points from external point p to circle (c,r)
vector<P> tangentFromPoint(P c, ld r, P p) {
	P v = p - c; ld d2 = norm(v);
	if (d2 < r * r - EPS) return {};
	if (d2 <= r * r + EPS) return {p};
	P m = c + v * (r * r / d2), h = perp(v) * (r * sqrtl(d2 - r * r) / d2);
	return {m + h, m - h};
}
// Common tangents, each as pair of tangent points (on circle1, circle2).
// Outer: tangents(c1,r1,c2,r2); inner: tangents(c1,r1,c2,-r2)
vector<pair<P, P>> tangents(P c1, ld r1, P c2, ld r2) {
	P d = c2 - c1; ld dr = r1 - r2, d2 = norm(d), h2 = d2 - dr * dr;
	if (d2 == 0 || h2 < -EPS) return {};
	vector<pair<P, P>> out;
	for (ld sg : {-1, 1}) {
		P v = (d * dr + perp(d) * sqrtl(max(h2, (ld)0)) * sg) / d2;
		out.push_back({c1 + v * r1, c2 + v * r2});
	}
	if (h2 <= EPS) out.pop_back();
	return out;
}
// Area of intersection of circle (c,r) and simple polygon (any orientation, signed by it)
ld circlePoly(P c, ld r, const vector<P> &ps) {
	auto arg = [&](P p, P q) { return atan2l(cross(p, q), dot(p, q)); };
	auto tri = [&](P p, P q) {
		ld r2 = r * r / 2; P d = q - p;
		ld a = dot(d, p) / norm(d), b = (norm(p) - r * r) / norm(d), det = a * a - b;
		if (det <= 0) return arg(p, q) * r2;
		ld s = max((ld)0, -a - sqrtl(det)), t = min((ld)1, -a + sqrtl(det));
		if (t < 0 || 1 <= s) return arg(p, q) * r2;
		P u = p + d * s, v = p + d * t;
		return arg(p, u) * r2 + cross(u, v) / 2 + arg(v, q) * r2;
	};
	ld sum = 0;
	for (size_t i = 0; i < ps.size(); i++)
		sum += tri(ps[i] - c, ps[(i + 1) % ps.size()] - c);
	return sum;
}
