using ll = long long;

// Divide and Conquer DP Optimization
// Use case:
// dp[i][j] = min_{k < j} (dp[i-1][k] + cost(k+1, j))
// when the argmin is monotone: opt[i][j] <= opt[i][j+1].
// Complexity: O(K * N * log N) for K layers and N states.

const ll DNC_INF = (ll)4e18;

// Replace this with your real cost function.
// This sample assumes you already can evaluate cost(l, r) in O(1).
ll cost(int l, int r, const vector<ll>& pref) {
    ll s = pref[r] - pref[l - 1];
    return s * s;
}

void computeLayer(
    int L,
    int R,
    int optL,
    int optR,
    const vector<ll>& prev,
    vector<ll>& cur,
    vector<int>& opt,
    const vector<ll>& pref
) {
    if (L > R) return;

    int mid = (L + R) >> 1;
    pair<ll, int> best = {DNC_INF, -1};

    int endK = min(mid - 1, optR);
    for (int k = optL; k <= endK; k++) {
        ll cand = prev[k] + cost(k + 1, mid, pref);
        if (cand < best.first) best = {cand, k};
    }

    cur[mid] = best.first;
    opt[mid] = best.second;

    computeLayer(L, mid - 1, optL, best.second, prev, cur, opt, pref);
    computeLayer(mid + 1, R, best.second, optR, prev, cur, opt, pref);
}

// Example: partition [1..N] into K groups with min total cost.
ll divideConquerDP(const vector<ll>& a, int K) {
    int N = (int)a.size() - 1; // 1-indexed, a[0] unused

    vector<ll> pref(N + 1, 0);
    for (int i = 1; i <= N; i++) pref[i] = pref[i - 1] + a[i];

    vector<ll> prev(N + 1, DNC_INF), cur(N + 1, DNC_INF);
    vector<int> opt(N + 1, 0);

    prev[0] = 0;
    for (int j = 1; j <= N; j++) prev[j] = cost(1, j, pref);

    for (int i = 2; i <= K; i++) {
        fill(cur.begin(), cur.end(), DNC_INF);
        computeLayer(1, N, 0, N - 1, prev, cur, opt, pref);
        prev.swap(cur);
    }

    return prev[N];
}

// Contest notes:
// 1) If monotonicity of opt does not hold, this optimization is invalid.
// 2) Precompute cost in O(1) when possible (prefix sums / prefix of prefix sums).
// 3) Boundaries depend on your DP definition; adjust k-range carefully.
