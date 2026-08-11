#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

/**
 * Divide and Conquer DP Optimization
 *
 * For DP of the form: dp[j] = min_{k < j} (dp[k] + cost(k, j))
 * where the optimal k for each j is monotonic (opt[j] <= opt[j+1]).
 *
 * Time complexity: O(n log n) instead of O(n^2)
 *
 * Usage:
 *   auto cost = [&](int k, int j) { return dp[k] + transCost(k, j); };
 *   vector<ll> ans = divide_conquer_dp(n, cost);
 */
vector<ll> divide_conquer_dp(int n, function<ll(int k, int j)> cost) {
    vector<ll> dp(n, INF);
    dp[0] = 0;

    // Recursive D&C: compute dp[l..r] given that dp[0..l-1] is computed
    function<void(int, int, int, int)> compute = [&](int l, int r, int optL, int optR) {
        if (l > r) return;
        int mid = (l + r) >> 1;
        pair<ll, int> best = {INF, -1};

        // Search for optimal k in [optL, min(mid-1, optR)]
        int upper = min(mid - 1, optR);
        for (int k = optL; k <= upper; ++k) {
            ll val = dp[k] + cost(k, mid);
            if (val < best.first) {
                best = {val, k};
            }
        }

        dp[mid] = best.first;
        int optK = best.second;

        // Left half: optimal k is in [optL, optK]
        compute(l, mid - 1, optL, optK);
        // Right half: optimal k is in [optK, optR]
        compute(mid + 1, r, optK, optR);
    };

    compute(1, n - 1, 0, n - 1);
    return dp;
}
