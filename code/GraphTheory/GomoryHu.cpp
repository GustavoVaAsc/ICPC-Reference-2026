// Gomory-Hu tree (Gusfield), n-1 max flows. Min cut(u,v) = min edge on tree path u-v.
// Undirected graph: addEdge(u,v,c). build() returns tree edges {i, parent[i], weight}.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct GomoryHu {
	struct E { int to; ll c, c0; };
	int n; vector<E> e; vector<vector<int>> g; vector<int> lvl, it;
	GomoryHu(int n) : n(n), g(n), lvl(n), it(n) {}
	void addEdge(int u, int v, ll c) {
		g[u].push_back(e.size()); e.push_back({v, c, c});
		g[v].push_back(e.size()); e.push_back({u, c, c});
	}
	bool bfs(int s, int t) {
		fill(lvl.begin(), lvl.end(), -1); lvl[s] = 0;
		queue<int> q; q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int id : g[u]) if (e[id].c > 0 && lvl[e[id].to] < 0) lvl[e[id].to] = lvl[u] + 1, q.push(e[id].to);
		}
		return lvl[t] >= 0;
	}
	ll dfs(int u, int t, ll f) {
		if (u == t) return f;
		for (int &i = it[u]; i < (int)g[u].size(); i++) {
			int id = g[u][i], v = e[id].to;
			if (e[id].c > 0 && lvl[v] == lvl[u] + 1)
				if (ll d = dfs(v, t, min(f, e[id].c))) { e[id].c -= d; e[id ^ 1].c += d; return d; }
		}
		return 0;
	}
	ll maxflow(int s, int t) {
		for (auto &x : e) x.c = x.c0;
		ll fl = 0;
		while (bfs(s, t)) { fill(it.begin(), it.end(), 0); while (ll d = dfs(s, t, LLONG_MAX)) fl += d; }
		return fl;
	}
	vector<array<ll, 3>> build() {
		vector<int> p(n, 0); vector<array<ll, 3>> tr;
		for (int i = 1; i < n; i++) {
			ll f = maxflow(i, p[i]);
			bfs(i, p[i]); // lvl[v] >= 0 <=> v on i's side of the min cut
			for (int j = i + 1; j < n; j++) if (lvl[j] >= 0 && p[j] == p[i]) p[j] = i;
			tr.push_back({i, p[i], f});
		}
		return tr;
	}
};
