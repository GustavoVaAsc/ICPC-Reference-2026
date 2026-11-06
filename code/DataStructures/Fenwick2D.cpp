// 2D Fenwick tree: point add, rectangle sum. O(log^2) per op. 1-indexed.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Fenwick2D {
	int n, m; vector<vector<ll>> t;
	Fenwick2D(int n, int m) : n(n), m(m), t(n + 1, vector<ll>(m + 1, 0)) {}
	void add(int x, int y, ll v) {
		for (int i = x; i <= n; i += i & -i) for (int j = y; j <= m; j += j & -j) t[i][j] += v;
	}
	ll pre(int x, int y) { // sum over [1..x] x [1..y]
		ll r = 0;
		for (int i = x; i > 0; i -= i & -i) for (int j = y; j > 0; j -= j & -j) r += t[i][j];
		return r;
	}
	ll query(int x1, int y1, int x2, int y2) { return pre(x2, y2) - pre(x1 - 1, y2) - pre(x2, y1 - 1) + pre(x1 - 1, y1 - 1); }
};
