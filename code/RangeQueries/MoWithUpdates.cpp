// Mo's algorithm with point updates (3D Mo), O(n^(5/3)). Example: number of distinct values in [l,r].
#include <bits/stdc++.h>
using namespace std;
const int N = 100005, V = 200005;
int n, B, a[N], cntv[V], distinctCnt;
struct Q { int l, r, t, id; };
struct U { int pos, oldv, newv; };
vector<Q> qs; vector<U> ups;
void add(int v) { if (cntv[v]++ == 0) distinctCnt++; }
void rem(int v) { if (--cntv[v] == 0) distinctCnt--; }
void applyUpd(int t, int l, int r, bool fwd) { // apply or undo update t
	auto &u = ups[t]; int v = fwd ? u.newv : u.oldv;
	if (l <= u.pos && u.pos <= r) { rem(a[u.pos]); add(v); }
	a[u.pos] = v;
}
vector<int> run() { // a[] must hold the initial array (0-indexed); ups[i].oldv = value before update i
	B = max(1, (int)cbrt((double)n * n));
	sort(qs.begin(), qs.end(), [&](const Q &x, const Q &y) {
		return make_tuple(x.l / B, x.r / B, x.t) < make_tuple(y.l / B, y.r / B, y.t);
	});
	vector<int> ans(qs.size());
	int L = 0, R = -1, T = 0; // T = number of applied updates
	for (auto &q : qs) {
		while (T < q.t) applyUpd(T++, L, R, true);
		while (T > q.t) applyUpd(--T, L, R, false);
		while (L > q.l) add(a[--L]);
		while (R < q.r) add(a[++R]);
		while (L < q.l) rem(a[L++]);
		while (R > q.r) rem(a[R--]);
		ans[q.id] = distinctCnt;
	}
	return ans;
}
// Query q: t = number of updates that happened before it.
