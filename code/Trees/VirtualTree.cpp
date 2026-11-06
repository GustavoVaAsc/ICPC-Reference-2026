// Virtual (auxiliary) tree on a set of key vertices, O(k log k) after LCA preprocessing.
// Needs tin/tout (euler tour) and lca(u,v). Returns edges (parent, child) of the compressed tree.
#include <bits/stdc++.h>
using namespace std;
const int N = 200005, LG = 18;
vector<int> g[N]; int tin[N], tout[N], up[LG][N], timer_;
void dfs(int v, int p) {
	tin[v] = timer_++; up[0][v] = p;
	for (int i = 1; i < LG; i++) up[i][v] = up[i - 1][up[i - 1][v]];
	for (int u : g[v]) if (u != p) dfs(u, v);
	tout[v] = timer_++;
}
bool anc(int a, int b) { return tin[a] <= tin[b] && tout[b] <= tout[a]; }
int lca(int a, int b) {
	if (anc(a, b)) return a;
	if (anc(b, a)) return b;
	for (int i = LG - 1; i >= 0; i--) if (!anc(up[i][a], b)) a = up[i][a];
	return up[0][a];
}
// call dfs(root, root) first (reset timer_ = 0 between tests; recursion depth n)
vector<pair<int, int>> virtualTree(vector<int> v) {
	auto cmp = [&](int a, int b) { return tin[a] < tin[b]; };
	sort(v.begin(), v.end(), cmp);
	for (int i = (int)v.size() - 1; i > 0; i--) v.push_back(lca(v[i - 1], v[i]));
	sort(v.begin(), v.end(), cmp);
	v.erase(unique(v.begin(), v.end()), v.end());
	vector<pair<int, int>> edges; vector<int> st;
	for (int x : v) {
		while (!st.empty() && !anc(st.back(), x)) st.pop_back();
		if (!st.empty()) edges.push_back({st.back(), x});
		st.push_back(x);
	}
	return edges;
}
