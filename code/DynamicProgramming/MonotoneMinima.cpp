// Monotone minima: for each row i find argmin_j cost(i,j) when opt(i) is non-decreasing
// (totally monotone matrix). Divide & conquer, O((n + m) log n); SMAWK would be O(n + m).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
ll cost(int i, int j); // user-defined
vector<int> opt;
void rec(int lo, int hi, int jl, int jr) { // rows [lo,hi], candidate cols [jl,jr]
	if (lo > hi) return;
	int mid = (lo + hi) / 2, best = jl; ll bv = LLONG_MAX;
	for (int j = jl; j <= jr; j++) {
		ll v = cost(mid, j);
		if (v < bv) bv = v, best = j;
	}
	opt[mid] = best;
	rec(lo, mid - 1, jl, best); rec(mid + 1, hi, best, jr);
}
void monotoneMinima() { opt.assign(n, 0); rec(0, n - 1, 0, m - 1); }
ll cost(int i, int j) { return (ll)(i - j) * (i - j); } // example
