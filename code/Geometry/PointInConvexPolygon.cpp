// Point in convex polygon (CCW, no collinear triples, n >= 3), O(log n). Boundary counts as inside.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct P { ll x, y; };
P operator-(P a, P b) { return {a.x - b.x, a.y - b.y}; }
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
bool inConvex(const vector<P> &p, P q) {
	int n = p.size(); P a = p[0];
	if (cross(p[1] - a, q - a) < 0 || cross(p[n - 1] - a, q - a) > 0) return false;
	int l = 1, r = n - 1;
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (cross(p[m] - a, q - a) >= 0) l = m; else r = m;
	}
	return cross(p[l + 1] - p[l], q - p[l]) >= 0;
}
