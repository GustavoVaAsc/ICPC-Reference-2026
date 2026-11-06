// Aliens trick / WQS binary search: cost(k) convex in k, need exactly k pieces.
// Add penalty lam per piece, solve unconstrained (run), binary search lam. O(log C * run).
// run is O(n^2) here; need K <= n. Example: split array into exactly K segments minimizing sum of (segment sum)^2.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, K; vector<ll> pre;
// returns {min of cost+lam*cnt, min cnt among optimal}
pair<ll, int> run(ll lam) {
	vector<ll> dp(n + 1, LLONG_MAX); vector<int> c(n + 1, 0);
	dp[0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < i; j++) {
			ll v = dp[j] + (pre[i] - pre[j]) * (pre[i] - pre[j]) + lam;
			if (v < dp[i] || (v == dp[i] && c[j] + 1 < c[i])) dp[i] = v, c[i] = c[j] + 1;
		}
	return {dp[n], c[n]};
}
ll aliens() {
	ll lo = 0, hi = pre[n] * pre[n] + 1; // (assumes pre[n]^2 fits ll) smallest lam with cnt <= K
	while (lo < hi) {
		ll mid = (lo + hi) / 2;
		if (run(mid).second <= K) hi = mid; else lo = mid + 1;
	}
	return run(lo).first - lo * K; // valid when K <= max useful count
}
