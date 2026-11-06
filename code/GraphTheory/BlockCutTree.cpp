// Block-cut tree (vertex-biconnected components), O(V+E).
// Tree nodes: 0..n-1 original vertices, n.. one node per block (adjacent to all its vertices).
// dfs is recursive (depth n); build once per object. Cut vertices = original nodes with degree > 1 in t. Isolated vertex stays alone.
#include <bits/stdc++.h>
using namespace std;
struct BCT {
	int n, T = 0;
	vector<vector<int>> g, t;
	vector<int> num, low, st;
	BCT(int n) : n(n), g(n), t(n), num(n), low(n) {}
	void add(int a, int b) { g[a].push_back(b); g[b].push_back(a); }
	void dfs(int v) {
		num[v] = low[v] = ++T; st.push_back(v);
		for (int u : g[v]) {
			if (num[u]) { low[v] = min(low[v], num[u]); continue; }
			dfs(u); low[v] = min(low[v], low[u]);
			if (low[u] >= num[v]) {
				t.emplace_back(); int b = t.size() - 1, x;
				do { x = st.back(); st.pop_back(); t[b].push_back(x); t[x].push_back(b); } while (x != u);
				t[b].push_back(v); t[v].push_back(b);
			}
		}
	}
	void build() { for (int v = 0; v < n; v++) if (!num[v]) dfs(v); }
};
