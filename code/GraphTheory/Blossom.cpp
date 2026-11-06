// Edmonds' blossom: maximum matching in general graph, O(V^3).
// add(a,b) edges (0-indexed), solve() returns size; mt[v] = partner or -1.
#include <bits/stdc++.h>
using namespace std;
struct Blossom {
	int n;
	vector<vector<int>> g;
	vector<int> mt, p, base, q;
	vector<bool> used, blossom;
	Blossom(int n) : n(n), g(n), mt(n, -1), p(n), base(n), used(n) {}
	void add(int a, int b) { g[a].push_back(b); g[b].push_back(a); }
	int lca(int a, int b) {
		vector<bool> u(n);
		for (;;) { a = base[a]; u[a] = true; if (mt[a] == -1) break; a = p[mt[a]]; }
		for (;;) { b = base[b]; if (u[b]) return b; b = p[mt[b]]; }
	}
	void mark(int v, int b, int ch) {
		while (base[v] != b) {
			blossom[base[v]] = blossom[base[mt[v]]] = true;
			p[v] = ch; ch = mt[v]; v = p[mt[v]];
		}
	}
	int find(int root) {
		fill(used.begin(), used.end(), false);
		fill(p.begin(), p.end(), -1);
		iota(base.begin(), base.end(), 0);
		used[root] = true; q.assign(1, root);
		for (size_t qh = 0; qh < q.size(); qh++) {
			int v = q[qh];
			for (int to : g[v]) {
				if (base[v] == base[to] || mt[v] == to) continue;
				if (to == root || (mt[to] != -1 && p[mt[to]] != -1)) {
					int cb = lca(v, to);
					blossom.assign(n, false);
					mark(v, cb, to); mark(to, cb, v);
					for (int i = 0; i < n; i++) if (blossom[base[i]]) {
						base[i] = cb;
						if (!used[i]) used[i] = true, q.push_back(i);
					}
				} else if (p[to] == -1) {
					p[to] = v;
					if (mt[to] == -1) return to;
					used[mt[to]] = true; q.push_back(mt[to]);
				}
			}
		}
		return -1;
	}
	int solve() {
		int res = 0;
		for (int i = 0; i < n; i++) if (mt[i] == -1) {
			int v = find(i);
			if (v == -1) continue;
			res++;
			while (v != -1) { int pv = p[v], ppv = mt[pv]; mt[v] = pv; mt[pv] = v; v = ppv; }
		}
		return res;
	}
};
