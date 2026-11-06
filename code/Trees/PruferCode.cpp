// Pruefer code: tree on n labeled vertices (0..n-1) <-> sequence of n-2 values. O(n).
#include <bits/stdc++.h>
using namespace std;
vector<int> pruferEncode(const vector<vector<int>> &g) { // g: adjacency of a tree
	int n = g.size();
	vector<int> deg(n), par(n, -1), code;
	function<void(int)> dfs = [&](int v) { for (int u : g[v]) if (u != par[v]) par[u] = v, dfs(u); };
	dfs(n - 1); // root at n-1
	for (int i = 0; i < n; i++) deg[i] = g[i].size();
	int ptr = 0;
	while (deg[ptr] != 1) ptr++;
	int leaf = ptr;
	for (int i = 0; i < n - 2; i++) {
		int nxt = par[leaf];
		code.push_back(nxt);
		if (--deg[nxt] == 1 && nxt < ptr) leaf = nxt;
		else { ptr++; while (deg[ptr] != 1) ptr++; leaf = ptr; }
	}
	return code;
}
vector<pair<int, int>> pruferDecode(const vector<int> &code) { // returns n-1 edges
	int n = code.size() + 2;
	vector<int> deg(n, 1);
	for (int x : code) deg[x]++;
	int ptr = 0;
	while (deg[ptr] != 1) ptr++;
	int leaf = ptr;
	vector<pair<int, int>> edges;
	for (int v : code) {
		edges.push_back({leaf, v});
		if (--deg[v] == 1 && v < ptr) leaf = v;
		else { ptr++; while (deg[ptr] != 1) ptr++; leaf = ptr; }
	}
	edges.push_back({leaf, n - 1});
	return edges;
}
