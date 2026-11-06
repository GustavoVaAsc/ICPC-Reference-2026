// Area of union of polygons (each CCW, simple), O(N^2) in total vertices (KACTL).
#include <bits/stdc++.h>
using namespace std;
typedef double ld;
struct P {
	ld x, y;
	P operator-(P o) const { return {x - o.x, y - o.y}; }
	ld cross(P o) const { return x * o.y - y * o.x; }
	ld cross(P a, P b) const { return (a - *this).cross(b - *this); }
	ld dot(P o) const { return x * o.x + y * o.y; }
};
int sgn(ld v) { return (v > 1e-9) - (v < -1e-9); }
int sideOf(P a, P b, P c) { return sgn(a.cross(b, c)); }
ld rat(P a, P b) { return sgn(b.x) ? a.x / b.x : a.y / b.y; }
ld polyUnion(const vector<vector<P>> &poly) {
	ld ret = 0;
	for (size_t i = 0; i < poly.size(); i++) for (size_t v = 0; v < poly[i].size(); v++) {
		P A = poly[i][v], B = poly[i][(v + 1) % poly[i].size()];
		vector<pair<ld, int>> segs = {{0, 0}, {1, 0}};
		for (size_t j = 0; j < poly.size(); j++) if (i != j)
			for (size_t u = 0; u < poly[j].size(); u++) {
				P C = poly[j][u], D = poly[j][(u + 1) % poly[j].size()];
				int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
				if (sc != sd) {
					ld sa = C.cross(D, A), sb = C.cross(D, B);
					if (min(sc, sd) < 0) segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
				} else if (!sc && !sd && j < i && sgn((B - A).dot(D - C)) > 0) {
					segs.emplace_back(rat(C - A, B - A), 1);
					segs.emplace_back(rat(D - A, B - A), -1);
				}
			}
		sort(segs.begin(), segs.end());
		for (auto &s : segs) s.first = min(max(s.first, (ld)0), (ld)1);
		ld sum = 0; int cnt = segs[0].second;
		for (size_t j = 1; j < segs.size(); j++) {
			if (!cnt) sum += segs[j].first - segs[j - 1].first;
			cnt += segs[j].second;
		}
		ret += A.cross(B) * sum;
	}
	return ret / 2;
}
