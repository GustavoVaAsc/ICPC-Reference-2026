// Monotonic queue DP: dp[i] = a[i] + min_{i-k <= j < i} dp[j], dp[0] = 0 (jump at most k). O(n).
// Generalizes to any dp[i] = cost(i) + min/max over a sliding window of earlier dp values.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll minPathCost(const vector<ll> &a, int k) { // a[1..n], cost to land on i; reach n from 0
	int n = a.size() - 1;
	vector<ll> dp(n + 1, 0);
	deque<int> dq{0};
	for (int i = 1; i <= n; i++) {
		while (dq.front() < i - k) dq.pop_front();
		dp[i] = a[i] + dp[dq.front()];
		while (!dq.empty() && dp[dq.back()] >= dp[i]) dq.pop_back();
		dq.push_back(i);
	}
	return dp[n];
}
