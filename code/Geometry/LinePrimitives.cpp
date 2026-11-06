// Line / segment primitives with complex<ld>. All O(1).
#include <bits/stdc++.h>
using namespace std;
typedef long double ld; typedef complex<ld> P;
const ld EPS = 1e-12;
ld cross(P a, P b) { return imag(conj(a) * b); }
ld dot(P a, P b) { return real(conj(a) * b); }
// Intersection of lines ab and cd; false if parallel (relative test)
bool lineInter(P a, P b, P c, P d, P &r) {
	ld x = cross(b - a, d - c);
	if (fabsl(x) <= EPS * abs(b - a) * abs(d - c)) return false;
	r = a + (b - a) * (cross(c - a, d - c) / x);
	return true;
}
bool onSeg(P p, P a, P b) {
	return fabsl(cross(b - a, p - a)) <= EPS * abs(b - a) * (abs(p - a) + 1) && dot(a - p, b - p) <= EPS;
}
// Segments ab and cd: single intersection point (parallel/collinear overlap -> false)
bool segInter(P a, P b, P c, P d, P &r) {
	ld x = cross(b - a, d - c);
	if (fabsl(x) <= EPS * abs(b - a) * abs(d - c)) return false;
	ld t = cross(c - a, d - c) / x, u = cross(c - a, b - a) / x;
	if (t < -EPS || t > 1 + EPS || u < -EPS || u > 1 + EPS) return false;
	r = a + (b - a) * t;
	return true;
}
P proj(P p, P a, P b) { return a + (b - a) * (dot(p - a, b - a) / norm(b - a)); }
P reflect(P p, P a, P b) { return proj(p, a, b) * (ld)2 - p; }
ld distLine(P p, P a, P b) { return fabsl(cross(b - a, p - a)) / abs(b - a); }
ld distSeg(P p, P a, P b) {
	if (dot(p - a, b - a) <= 0) return abs(p - a);
	if (dot(p - b, a - b) <= 0) return abs(p - b);
	return distLine(p, a, b);
}
