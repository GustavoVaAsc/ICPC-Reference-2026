// Half-plane intersection, O(n log n). Region = LEFT side of directed line p->q.
// Returns polygon vertices (CCW), empty if empty/degenerate. Bounded by a big box.
#include <bits/stdc++.h>
using namespace std;
typedef long double ld; typedef complex<ld> P;
const ld EPS = 1e-12, INF = 1e9;
ld cross(P a, P b) { return imag(conj(a) * b); }
ld dot(P a, P b) { return real(conj(a) * b); }
struct HP {
	P p, pq; ld ang;
	HP(P a, P b) : p(a), pq(b - a), ang(atan2l(pq.imag(), pq.real())) {}
	bool out(P r) const { return cross(pq, r - p) < -EPS; }
	bool operator<(const HP &e) const { return ang < e.ang; }
};
P inter(const HP &s, const HP &t) {
	return s.p + s.pq * (cross(t.p - s.p, t.pq) / cross(s.pq, t.pq));
}
vector<P> hpi(vector<HP> H) {
	P box[4] = {P(INF, INF), P(-INF, INF), P(-INF, -INF), P(INF, -INF)};
	for (int i = 0; i < 4; i++) H.push_back(HP(box[i], box[(i + 1) % 4]));
	sort(H.begin(), H.end());
	deque<HP> dq; int len = 0;
	for (auto &h : H) {
		while (len > 1 && h.out(inter(dq[len - 1], dq[len - 2]))) dq.pop_back(), --len;
		while (len > 1 && h.out(inter(dq[0], dq[1]))) dq.pop_front(), --len;
		if (len > 0 && fabsl(cross(h.pq, dq[len - 1].pq)) < EPS) {
			if (dot(h.pq, dq[len - 1].pq) < 0) return {};
			if (h.out(dq[len - 1].p)) dq.pop_back(), --len;
			else continue;
		}
		dq.push_back(h); ++len;
	}
	while (len > 2 && dq[0].out(inter(dq[len - 1], dq[len - 2]))) dq.pop_back(), --len;
	while (len > 2 && dq[len - 1].out(inter(dq[0], dq[1]))) dq.pop_front(), --len;
	if (len < 3) return {};
	vector<P> ret(len);
	for (int i = 0; i < len; i++) ret[i] = inter(dq[i], dq[(i + 1) % len]);
	return ret;
}
