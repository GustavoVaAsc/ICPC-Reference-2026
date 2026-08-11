#include <vector>
#include <climits>

// Knuth's Optimization for DP with quadrangle inequality
// dp[i][j] = min over k of (dp[i][k] + dp[k][j]) + C[i][j]
// Reduces O(N^3) to O(N^2) when cost matrix C satisfies quadrangle inequality
// and monotonicity of optimal split points.

using namespace std;

vector<vector<long long>> knuth_dp(int n, const vector<vector<long long>>& cost) {
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n, 0));

    // Base case: opt[i][i] = i
    for (int i = 0; i < n; i++) {
        opt[i][i] = i;
    }

    // Increasing interval length
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;

            // Search for optimal k in [opt[i][j-1], opt[i+1][j]]
            int start = opt[i][j - 1];
            int end = (i + 1 < n) ? opt[i + 1][j] : j;

            long long best = LLONG_MAX;
            int bestK = start;

            for (int k = start; k <= end; k++) {
                long long val = dp[i][k] + dp[k][j] + cost[i][j];
                if (val < best) {
                    best = val;
                    bestK = k;
                }
            }

            dp[i][j] = best;
            opt[i][j] = bestK;
        }
    }

    return dp;
}
