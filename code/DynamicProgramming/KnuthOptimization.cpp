using ll = long long;

// Knuth Optimization
// Optimizes DP of the form:
// dp[l][r] = min_{k in [l, r-1]} (dp[l][k] + dp[k+1][r] + cost(l, r))
// with opt[l][r-1] <= opt[l][r] <= opt[l+1][r].
// Typical complexity: O(N^2) instead of O(N^3).
// Common use cases: optimal BST / optimal merge-like interval DP with quadrangle inequality.
// Caveat: Knuth's bound needs the quadrangle inequality and interval monotonicity; the shipped intervalCost
// meets the former with equality, but the latter needs a[i] >= 0, else the search range may miss the optimum (wrong answer).

const ll KNUTH_INF = (ll)4e18;

// Example cost: sum of a[l..r] (1-indexed).
// Replace this with your problem's cost function.
ll intervalCost(int l, int r, const vector<ll>& pref) {
    return pref[r] - pref[l - 1];
}

// Returns minimum total cost for partitioning/merging interval [1..n].
ll knuthOptimization(const vector<ll>& a) {
    int n = (int)a.size() - 1; // expects 1-indexed input, a[0] unused

    vector<ll> pref(n + 1, 0);
    for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i];

    vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, 0));
    vector<vector<int>> opt(n + 2, vector<int>(n + 2, 0));

    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = KNUTH_INF;

            // Knuth bound: opt[l][r-1] <= opt[l][r] <= opt[l+1][r]; k splits as [l..k] + [k+1..r],
            // so k must stay in [l, r-1] (the raw bound may reach r when len == 2).
            int start = opt[l][r - 1];
            int finish = min(opt[l + 1][r], r - 1);

            for (int k = start; k <= finish; k++) {
                ll cand = dp[l][k] + dp[k + 1][r] + intervalCost(l, r, pref);
                if (cand < dp[l][r]) {
                    dp[l][r] = cand;
                    opt[l][r] = k;
                }
            }
        }
    }

    return dp[1][n];
}

// Example of use:
// int n; cin >> n;
// vector<ll> a(n + 1);
// for (int i = 1; i <= n; i++) cin >> a[i];
// cout << knuthOptimization(a) << '\n';
