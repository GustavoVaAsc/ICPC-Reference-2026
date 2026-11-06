// DSU on Tree (a.k.a. Sack)
// Main use cases:
// 1) For each node, answer subtree queries depending on color/value frequencies.
// 2) Typical queries: distinct colors in subtree, max frequency color sum, etc.
// Complexity: O(N log N) with vector merges or O(N log N) / O(N sqrt N) variants.

struct DSUOnTree {
    int n;
    vector<vector<int>> g;
    vector<int> color;

    vector<int> sz, heavy, st, en, ver;
    int timer = 0;

    // Example payload: distinct colors in current active set.
    vector<int> freq;
    int distinct = 0;
    vector<int> answer;

    DSUOnTree(int n_, const vector<int>& color_, int maxColor)
        : n(n_), g(n_), color(color_), sz(n_, 0), heavy(n_, -1),
          st(n_, 0), en(n_, 0), ver(n_, 0), freq(maxColor + 1, 0), answer(n_, 0) {}

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfsSize(int u, int p) {
        sz[u] = 1;
        st[u] = timer;
        ver[timer++] = u;

        int bestSize = 0;
        for (int v : g[u]) {
            if (v == p) continue;
            dfsSize(v, u);
            sz[u] += sz[v];
            if (sz[v] > bestSize) {
                bestSize = sz[v];
                heavy[u] = v;
            }
        }
        en[u] = timer - 1;
    }

    void addNode(int u) {
        if (++freq[color[u]] == 1) distinct++;
    }

    void removeNode(int u) {
        if (--freq[color[u]] == 0) distinct--;
    }

    void addSubtree(int u) {
        for (int t = st[u]; t <= en[u]; t++) addNode(ver[t]);
    }

    void removeSubtree(int u) {
        for (int t = st[u]; t <= en[u]; t++) removeNode(ver[t]);
    }

    void dfs(int u, int p, bool keep) {
        for (int v : g[u]) {
            if (v == p || v == heavy[u]) continue;
            dfs(v, u, false);
        }

        if (heavy[u] != -1) dfs(heavy[u], u, true);

        for (int v : g[u]) {
            if (v == p || v == heavy[u]) continue;
            addSubtree(v);
        }

        addNode(u);
        answer[u] = distinct; // Example answer for node u

        if (!keep) {
            removeSubtree(u);
        }
    }

    vector<int> solve(int root = 0) {
        dfsSize(root, -1);
        dfs(root, -1, true);
        return answer;
    }
};

// Contest note:
// To support other query types, replace addNode/removeNode and answer assignment only.
