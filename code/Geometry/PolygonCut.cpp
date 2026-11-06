// Cut polygon (any simple polygon, CCW) with half-plane: keep the LEFT side of line a->b. O(n).
// Convex polygon clipping by convex clip polygon: cut by each of its edges in turn.
#include <bits/stdc++.h>
using namespace std;
typedef double ld; typedef complex<ld> P;
ld cross(P a, P b) { return imag(conj(a) * b); }
vector<P> cutPolygon(const vector<P> &poly, P a, P b) {
	vector<P> res; int n = poly.size();
	for (int i = 0; i < n; i++) {
		P p = poly[i], q = poly[(i + 1) % n];
		ld cp = cross(b - a, p - a), cq = cross(b - a, q - a);
		if (cp >= 0) res.push_back(p);
		if ((cp > 0 && cq < 0) || (cp < 0 && cq > 0))
			res.push_back(p + (q - p) * (cp / (cp - cq)));
	}
	return res;
}
