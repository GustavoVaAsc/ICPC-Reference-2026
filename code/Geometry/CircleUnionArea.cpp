// Area of union of circles, O(n^2 log n). Green's theorem on uncovered arcs.
#include <bits/stdc++.h>
using namespace std;
typedef double ld;
struct C { ld x, y, r; };
const ld PI = acos(-1.0);
ld unionArea(vector<C> c) {
	int n = c.size(); ld area = 0;
	for (int i = 0; i < n; i++) {
		vector<pair<ld, ld>> iv; bool covered = false;
		for (int j = 0; j < n && !covered; j++) if (j != i) {
			ld dx = c[j].x - c[i].x, dy = c[j].y - c[i].y, d = hypot(dx, dy);
			if (d + c[i].r <= c[j].r && (d > 1e-12 || c[i].r < c[j].r || j < i)) { covered = true; break; }
			if (d >= c[i].r + c[j].r || d + c[j].r <= c[i].r) continue;
			ld a = atan2(dy, dx), b = acos((c[i].r * c[i].r + d * d - c[j].r * c[j].r) / (2 * c[i].r * d));
			ld lo = a - b, hi = a + b;
			while (lo < 0) lo += 2 * PI, hi += 2 * PI;
			while (lo >= 2 * PI) lo -= 2 * PI, hi -= 2 * PI;
			if (hi > 2 * PI) iv.push_back({lo, 2 * PI}), iv.push_back({0, hi - 2 * PI});
			else iv.push_back({lo, hi});
		}
		if (covered) continue;
		iv.push_back({2 * PI, 2 * PI});
		sort(iv.begin(), iv.end());
		ld cur = 0;
		auto arc = [&](ld t1, ld t2) {
			area += 0.5 * (c[i].r * c[i].r * (t2 - t1) + c[i].x * c[i].r * (sin(t2) - sin(t1)) - c[i].y * c[i].r * (cos(t2) - cos(t1)));
		};
		for (auto [l, h] : iv) {
			if (l > cur) arc(cur, l);
			cur = max(cur, h);
		}
	}
	return area;
}
