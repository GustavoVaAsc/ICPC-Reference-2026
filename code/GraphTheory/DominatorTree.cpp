// Dominator tree (Lengauer-Tarjan, path compression), O(E log V).
// addEdge(u,v) directed; run(root) -> idom[v] (root: root itself, unreachable: -1).
#include <bits/stdc++.h>
using namespace std;
struct DomTree {
	int n, T = 0;
	vector<vector<int>> g, rg, bucket;
	vector<int> arr, rev, par, sdom, idom, dsu, label, res;
	DomTree(int n) : n(n), g(n), rg(n), bucket(n), arr(n, -1), rev(n), par(n), sdom(n), idom(n), dsu(n), label(n) {}
	void addEdge(int u, int v) { g[u].push_back(v); }
	void dfs(int u) {
		arr[u] = T; rev[T] = u; label[T] = sdom[T] = dsu[T] = T; T++;
		for (int w : g[u]) {
			if (arr[w] == -1) { dfs(w); par[arr[w]] = arr[u]; }
			rg[arr[w]].push_back(arr[u]);
		}
	}
	int find(int u, int x = 0) {
		if (u == dsu[u]) return x ? -1 : u;
		int v = find(dsu[u], x + 1);
		if (v < 0) return u;
		if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
		dsu[u] = v;
		return x ? v : label[u];
	}
	vector<int> run(int root) {
		dfs(root);
		for (int i = T - 1; i >= 0; i--) {
			for (int w : rg[i]) sdom[i] = min(sdom[i], sdom[find(w)]);
			if (i) bucket[sdom[i]].push_back(i);
			for (int w : bucket[i]) {
				int v = find(w);
				idom[w] = (sdom[v] == sdom[w]) ? sdom[w] : v;
			}
			if (i > 1) dsu[i] = par[i];
		}
		for (int i = 1; i < T; i++) if (idom[i] != sdom[i]) idom[i] = idom[idom[i]];
		res.assign(n, -1);
		res[root] = root;
		for (int i = 1; i < T; i++) res[rev[i]] = rev[idom[i]];
		return res;
	}
};
