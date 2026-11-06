// Rotating calipers on strictly convex polygon h (CCW, n >= 3, integer coords). O(n).
// diameter2: squared farthest pair distance. width2: squared min width (as ld).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef long double ld;
struct P { ll x, y; };
P operator-(P a, P b) { return {a.x - b.x, a.y - b.y}; }
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
ll d2(P a, P b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
ll diameter2(const vector<P> &h) {
	int n = h.size(), j = 1; ll best = 0;
	for (int i = 0; i < n; i++) {
		while (cross(h[(i + 1) % n] - h[i], h[(j + 1) % n] - h[j]) > 0) j = (j + 1) % n;
		best = max({best, d2(h[i], h[j]), d2(h[(i + 1) % n], h[j])});
	}
	return best;
}
ld width2(const vector<P> &h) {
	int n = h.size(), j = 1; ld best = 1e30;
	for (int i = 0; i < n; i++) {
		P e = h[(i + 1) % n] - h[i];
		while (cross(e, h[(j + 1) % n] - h[i]) > cross(e, h[j] - h[i])) j = (j + 1) % n;
		ld c = cross(e, h[j] - h[i]);
		best = min(best, c * c / (ld)(e.x * e.x + e.y * e.y));
	}
	return best;
}
