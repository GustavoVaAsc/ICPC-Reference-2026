// Unrooted tree isomorphism: canonical id from center(s). Exact (no hash collisions), O(n log n).
// Two trees are isomorphic iff canon(g1) == canon(g2) (share the same `ids` map across calls).
#include <bits/stdc++.h>
using namespace std;
map<vector<int>, int> ids;
int rootedId(const vector<vector<int>> &g, int v, int p) {
	vector<int> ch;
	for (int u : g[v]) if (u != p) ch.push_back(rootedId(g, u, v));
	sort(ch.begin(), ch.end());
	return ids.emplace(ch, ids.size()).first->second;
}
vector<int> centers(const vector<vector<int>> &g) {
	int n = g.size();
	vector<int> deg(n), cur, nxt;
	for (int i = 0; i < n; i++) if ((deg[i] = g[i].size()) <= 1) cur.push_back(i);
	int left = n;
	while (left > 2) {
		left -= cur.size(); nxt.clear();
		for (int v : cur) for (int u : g[v]) if (--deg[u] == 1) nxt.push_back(u);
		cur = nxt;
	}
	return cur;
}
int canon(const vector<vector<int>> &g) {
	int best = INT_MAX;
	for (int c : centers(g)) best = min(best, rootedId(g, c, -1));
	return best;
}
