// Mo's algorithm on trees: queries on path u-v (distinct values on the path). O((n+q) sqrt n).
// Euler tour of size 2n; a vertex seen twice in the window is toggled out.
#include <bits/stdc++.h>
using namespace std;
const int N = 100005, LG = 17;
vector<int> g[N]; int val[N], tin[N], tout[N], up[LG][N], ord[2 * N], T_, B;
int cntv[N], inSet[N], distinctCnt;
void dfs(int v, int p) {
	tin[v] = T_; ord[T_++] = v; up[0][v] = p;
	for (int i = 1; i < LG; i++) up[i][v] = up[i - 1][up[i - 1][v]];
	for (int u : g[v]) if (u != p) dfs(u, v);
	tout[v] = T_; ord[T_++] = v;
}
bool anc(int a, int b) { return tin[a] <= tin[b] && tout[b] <= tout[a]; }
int lca(int a, int b) {
	if (anc(a, b)) return a;
	if (anc(b, a)) return b;
	for (int i = LG - 1; i >= 0; i--) if (!anc(up[i][a], b)) a = up[i][a];
	return up[0][a];
}
void toggle(int v) {
	if (inSet[v] ^= 1) { if (cntv[val[v]]++ == 0) distinctCnt++; }
	else if (--cntv[val[v]] == 0) distinctCnt--;
}
struct Q { int l, r, lc, id; };
vector<int> solve(int n, vector<pair<int, int>> pq) { // dfs(root, root) already called; pq = (u, v)
	B = max(1, (int)(2 * n / sqrt((double)pq.size() + 1)));
	vector<Q> qs;
	for (int i = 0; i < (int)pq.size(); i++) {
		auto [u, v] = pq[i];
		if (tin[u] > tin[v]) swap(u, v);
		int c = lca(u, v);
		if (c == u) qs.push_back({tin[u], tin[v], -1, i});
		else qs.push_back({tout[u], tin[v], c, i});
	}
	sort(qs.begin(), qs.end(), [&](const Q &a, const Q &b) {
		if (a.l / B != b.l / B) return a.l < b.l;
		return (a.l / B & 1) ? a.r > b.r : a.r < b.r;
	});
	vector<int> ans(pq.size());
	int L = 0, R = -1;
	for (auto &q : qs) {
		while (L > q.l) toggle(ord[--L]);
		while (R < q.r) toggle(ord[++R]);
		while (L < q.l) toggle(ord[L++]);
		while (R > q.r) toggle(ord[R--]);
		if (q.lc != -1) toggle(q.lc);
		ans[q.id] = distinctCnt;
		if (q.lc != -1) toggle(q.lc);
	}
	return ans;
}
