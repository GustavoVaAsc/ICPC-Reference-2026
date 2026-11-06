// Bitset subset-sum / bounded knapsack feasibility. O(n * S / 64).
// Bounded copies: binary splitting (cnt -> 1,2,4,...,rest), O(n log c * S / 64).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int S = 100001;
bitset<S> reachable(const vector<pair<int, int>> &items) { // (weight, count)
	bitset<S> dp; dp[0] = 1;
	for (auto [w, c] : items)
		for (int k = 1; c > 0; k <<= 1) {
			int t = min(k, c); c -= t;
			if ((ll)w * t >= S) continue;
			dp |= dp << (w * t);
		}
	return dp;
}
