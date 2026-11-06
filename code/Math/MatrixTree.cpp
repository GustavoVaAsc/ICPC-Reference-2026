// Matrix-tree theorem (Kirchhoff): #spanning trees = any cofactor of Laplacian L = D - A (multi-edges count).
// Directed (out-trees from root r): L[v][v] = indeg(v), L[u][v] -= 1 per edge u->v; delete row/col r.
// Determinant mod prime via Gaussian elimination, O(n^3).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
ll pw(ll b, ll e) { ll r = 1; for (b %= MOD; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD; return r; }
ll detMod(vector<vector<ll>> a) {
	int n = a.size(); ll res = 1;
	for (int i = 0; i < n; i++) {
		int p = i;
		while (p < n && a[p][i] == 0) p++;
		if (p == n) return 0;
		if (p != i) swap(a[p], a[i]), res = (MOD - res) % MOD;
		res = res * a[i][i] % MOD;
		ll iv = pw(a[i][i], MOD - 2);
		for (int j = i + 1; j < n; j++) {
			ll f = a[j][i] * iv % MOD;
			for (int k = i; k < n; k++) a[j][k] = ((a[j][k] - f * a[i][k]) % MOD + MOD) % MOD;
		}
	}
	return res;
}
ll countSpanningTrees(int n, const vector<pair<int, int>> &edges) { // undirected multigraph
	vector<vector<ll>> L(n, vector<ll>(n, 0));
	for (auto [u, v] : edges) {
		L[u][u]++; L[v][v]++; L[u][v]--; L[v][u]--;
	}
	for (auto &r : L) for (ll &x : r) x = (x % MOD + MOD) % MOD;
	L.pop_back(); for (auto &r : L) r.pop_back();
	return detMod(L);
}
