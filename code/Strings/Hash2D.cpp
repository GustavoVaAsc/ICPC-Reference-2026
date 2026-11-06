// 2D polynomial hash (mod 2^61-1): hash of any submatrix in O(1); count occurrences of a pattern in a grid.
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull MOD = (1ULL << 61) - 1;
ull mul(ull a, ull b) { __uint128_t t = (__uint128_t)a * b; ull r = (t & MOD) + (t >> 61); return r >= MOD ? r - MOD : r; }
ull ad(ull a, ull b) { a += b; return a >= MOD ? a - MOD : a; }
ull sb(ull a, ull b) { return a >= b ? a - b : a + MOD - b; }
struct Hash2D {
	int n, m; ull bx, by; vector<vector<ull>> h; vector<ull> px, py;
	Hash2D(const vector<string> &g, ull bx, ull by) : n(g.size()), m(g[0].size()), bx(bx), by(by), h(n + 1, vector<ull>(m + 1, 0)), px(n + 1, 1), py(m + 1, 1) {
		for (int i = 1; i <= n; i++) px[i] = mul(px[i - 1], bx);
		for (int j = 1; j <= m; j++) py[j] = mul(py[j - 1], by);
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
			h[i + 1][j + 1] = sb(ad(ad(mul(h[i][j + 1], bx), mul(h[i + 1][j], by)), g[i][j]), mul(mul(h[i][j], bx), by));
	}
	ull get(int x1, int y1, int x2, int y2) { // rows [x1,x2), cols [y1,y2)
		ull r = sb(h[x2][y2], mul(h[x1][y2], px[x2 - x1]));
		r = sb(r, mul(h[x2][y1], py[y2 - y1]));
		return ad(r, mul(mul(h[x1][y1], px[x2 - x1]), py[y2 - y1]));
	}
};
// Count occurrences of pattern p in grid g (use same random bases for both).
int countPattern(const vector<string> &g, const vector<string> &p) {
	mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	ull bx = rng() % (MOD - 1000) + 500, by = rng() % (MOD - 1000) + 500;
	Hash2D A(g, bx, by), B(p, bx, by);
	int ph = p.size(), pw = p[0].size(), cnt = 0;
	ull target = B.get(0, 0, ph, pw);
	for (int i = 0; i + ph <= A.n; i++) for (int j = 0; j + pw <= A.m; j++) cnt += A.get(i, j, i + ph, j + pw) == target;
	return cnt;
}
