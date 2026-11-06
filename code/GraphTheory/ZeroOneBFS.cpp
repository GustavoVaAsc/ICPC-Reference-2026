// 0-1 BFS: shortest paths with edge weights in {0,1}, O(V+E).
// g[u] = {(v, w)}. Returns dist (INF if unreachable).
#include <bits/stdc++.h>
using namespace std;
vector<int> bfs01(const vector<vector<pair<int, int>>> &g, int s) {
	const int INF = 1e9;
	vector<int> d(g.size(), INF);
	deque<int> dq;
	d[s] = 0; dq.push_back(s);
	while (!dq.empty()) {
		int u = dq.front(); dq.pop_front();
		for (auto [v, w] : g[u]) if (d[u] + w < d[v]) {
			d[v] = d[u] + w;
			if (w) dq.push_back(v); else dq.push_front(v);
		}
	}
	return d;
}
