// Generic Rerooting DP template
// Main use cases:
// 1) Compute answer for every node as root in O(N).
// 2) Tree DP where combine operation is associative.
// 3) Examples: subtree sizes, distance sums, max path through root, etc.

template <typename T>
struct RerootingDP {
    int n;
    vector<vector<int>> g;
    vector<T> down, allAns;

    T identity;
    function<T(const T&, const T&)> merge; // associative merge
    function<T(const T&, int, int)> addRoot; // add edge/node contribution (child->parent)

    RerootingDP(
        int n_,
        T identity_,
        function<T(const T&, const T&)> merge_,
        function<T(const T&, int, int)> addRoot_
    ) : n(n_), g(n_), down(n_, identity_), allAns(n_, identity_),
        identity(identity_), merge(merge_), addRoot(addRoot_) {}

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfsDown(int u, int p) {
        T acc = identity;
        for (int v : g[u]) {
            if (v == p) continue;
            dfsDown(v, u);
            acc = merge(acc, addRoot(down[v], v, u));
        }
        down[u] = acc;
    }

    void dfsUp(int u, int p, const T &fromParent) {
        int m = (int)g[u].size();
        vector<T> pref(m + 1, identity), suf(m + 1, identity);

        for (int i = 0; i < m; i++) {
            int v = g[u][i];
            T val = (v == p ? fromParent : addRoot(down[v], v, u));
            pref[i + 1] = merge(pref[i], val);
        }

        for (int i = m - 1; i >= 0; i--) {
            int v = g[u][i];
            T val = (v == p ? fromParent : addRoot(down[v], v, u));
            suf[i] = merge(suf[i + 1], val);
        }

        allAns[u] = pref[m];

        for (int i = 0; i < m; i++) {
            int v = g[u][i];
            if (v == p) continue;
            T withoutV = merge(pref[i], suf[i + 1]);
            dfsUp(v, u, addRoot(withoutV, u, v));
        }
    }

    vector<T> solve(int root = 0) {
        dfsDown(root, -1);
        dfsUp(root, -1, identity);
        return allAns;
    }
};

// Example use case: subtree size from every root (toy merge = sum).
// Replace merge/addRoot for your problem-specific transitions.
