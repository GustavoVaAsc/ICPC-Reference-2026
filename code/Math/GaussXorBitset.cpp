// Gaussian elimination over GF(2) with bitset, O(n * m * n / 64).
// Solves A x = b (n equations, m <= M unknowns). Row i: bits 0..m-1 = A, bit M = b.
// Returns rank, or -1 if inconsistent; x holds one solution (free vars = 0).
#include <bits/stdc++.h>
using namespace std;
const int M = 1005;
int gaussXor(vector<bitset<M + 1>> a, int m, bitset<M> &x) {
	int n = a.size(), rk = 0; vector<int> where(m, -1);
	for (int c = 0; c < m && rk < n; c++) {
		int p = rk;
		while (p < n && !a[p][c]) p++;
		if (p == n) continue;
		swap(a[p], a[rk]); where[c] = rk;
		for (int i = 0; i < n; i++) if (i != rk && a[i][c]) a[i] ^= a[rk];
		rk++;
	}
	for (int i = rk; i < n; i++) if (a[i][M]) return -1;
	x.reset();
	for (int c = 0; c < m; c++) if (where[c] != -1) x[c] = a[where[c]][M];
	return rk;
}
