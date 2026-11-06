// Broken-profile DP: count domino tilings of n x m grid (cells marked blocked[i][j] are skipped).
// Mask bit j = cell (i,j) (not yet processed) or (i+1,j) (processed) already filled. O(n * m * 2^m).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll tilings(int n, int m, const vector<string> &g) { // g[i][j] == '#' blocked
	vector<ll> dp(1 << m, 0), nd(1 << m);
	dp[0] = 1;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		fill(nd.begin(), nd.end(), 0);
		for (int mask = 0; mask < (1 << m); mask++) if (dp[mask]) {
			ll v = dp[mask];
			bool filled = mask >> j & 1;
			if (g[i][j] == '#') { if (!filled) nd[mask] += v; continue; } // blocked cell must stay empty
			if (filled) { nd[mask ^ (1 << j)] += v; continue; }
			nd[mask | (1 << j)] += v; // vertical domino: fills (i+1, j)
			if (j + 1 < m && !(mask >> (j + 1) & 1) && g[i][j + 1] != '#')
				nd[mask | (1 << (j + 1))] += v; // horizontal domino: fills (i, j+1) (bit j+1 = current row)
		}
		swap(dp, nd);
	}
	return dp[0];
}
