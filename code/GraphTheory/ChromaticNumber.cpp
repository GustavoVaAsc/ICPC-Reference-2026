// Chromatic number, n <= ~20, O(2^n * n) (inclusion-exclusion over independent sets, mod prime).
// chi = min k with sum_S (-1)^(n-|S|) * ind(S)^k != 0, ind(S) = #independent subsets of S.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
int chromatic(int n, const vector<int> &adj) { // adj[i] = neighbour bitmask
	vector<ll> ind(1 << n), pw(1 << n, 1);
	ind[0] = 1;
	for (int S = 1; S < (1 << n); S++) {
		int v = __builtin_ctz(S);
		ind[S] = (ind[S ^ (1 << v)] + ind[S & ~(1 << v) & ~adj[v]]) % MOD;
	}
	for (int k = 1; k <= n; k++) {
		ll sum = 0;
		for (int S = 0; S < (1 << n); S++) {
			pw[S] = pw[S] * ind[S] % MOD;
			sum += ((n - __builtin_popcount(S)) & 1) ? MOD - pw[S] : pw[S];
		}
		if (sum % MOD) return k;
	}
	return n;
}
