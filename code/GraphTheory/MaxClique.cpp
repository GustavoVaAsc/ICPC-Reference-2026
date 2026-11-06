// Maximum clique (Bron-Kerbosch with pivoting + bound), n <= 64. Fast in practice (~3^(n/3) worst).
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int n, best; ull adj[64]; // adj[i] bitmask of neighbours
void bk(int sz, ull P, ull X) {
	if (!P) { if (!X) best = max(best, sz); return; }
	if (sz + __builtin_popcountll(P) <= best) return;
	int u = -1, bc = -1;
	for (ull m = P | X; m; m &= m - 1) {
		int c = __builtin_popcountll(P & adj[__builtin_ctzll(m)]);
		if (c > bc) bc = c, u = __builtin_ctzll(m);
	}
	for (ull m = P & ~adj[u]; m; m &= m - 1) {
		int v = __builtin_ctzll(m);
		bk(sz + 1, P & adj[v], X & adj[v]);
		P &= ~(1ULL << v); X |= 1ULL << v;
	}
}
int maxClique() { best = 0; bk(0, n == 64 ? ~0ULL : (1ULL << n) - 1, 0); return best; }
