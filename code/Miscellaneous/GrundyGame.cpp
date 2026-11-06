// Grundy / Nim game template
// Main use cases:
// 1) Impartial combinatorial games (normal play).
// 2) Build move graph, compute Grundy numbers with mex.
// 3) Multiple independent piles/components: xor of Grundy values decides winner.

int mex(vector<int> v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int g = 0;
    for (int x : v) {
        if (x == g) g++;
        else if (x > g) break;
    }
    return g;
}

// Example 1: subtraction game.
// Allowed moves: remove values in moves[] from pile size n.
struct SubtractionGame {
    vector<int> moves;
    vector<int> dp;

    explicit SubtractionGame(const vector<int> &moves_) : moves(moves_) {}

    int grundy(int n) {
        dp.assign(n + 1, 0);
        for (int x = 1; x <= n; x++) {
            vector<int> nxt;
            for (int mv : moves) {
                if (x >= mv) nxt.push_back(dp[x - mv]);
            }
            dp[x] = mex(nxt);
        }
        return dp[n];
    }
};

// Example 2: DAG game with memoized DFS.
struct DAGGrundy {
    int n;
    vector<vector<int>> g;
    vector<int> memo;

    explicit DAGGrundy(int n_) : n(n_), g(n_), memo(n_, -1) {}

    void addEdge(int u, int v) { g[u].push_back(v); }

    int solve(int u) {
        if (memo[u] != -1) return memo[u];
        vector<int> nextGrundy;
        for (int v : g[u]) nextGrundy.push_back(solve(v));
        return memo[u] = mex(nextGrundy);
    }
};

// Winner rule:
// If xor of starting positions' Grundy values != 0 => First player wins.
