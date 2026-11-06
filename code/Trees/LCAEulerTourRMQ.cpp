// LCA with Euler Tour + RMQ (Sparse Table)
// Main use cases:
// 1) Static tree, many LCA queries.
// 2) Need O(1) query time after O(N log N) preprocessing.
// 3) Also useful for distance queries: dist(u,v)=depth[u]+depth[v]-2*depth[lca].

struct LCAEulerTourRMQ {
    int n;
    vector<vector<int>> g;
    vector<int> first, depthNode;

    vector<int> euler, depthEuler;
    vector<vector<int>> st; // stores index in euler array with minimum depth
    vector<int> lg;

    explicit LCAEulerTourRMQ(int n_) : n(n_), g(n_), first(n_, -1), depthNode(n_, 0) {}

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int u, int p, int d) {
        depthNode[u] = d;
        first[u] = (int)euler.size();
        euler.push_back(u);
        depthEuler.push_back(d);

        for (int v : g[u]) {
            if (v == p) continue;
            dfs(v, u, d + 1);
            euler.push_back(u);
            depthEuler.push_back(d);
        }
    }

    void build(int root = 0) {
        euler.clear();
        depthEuler.clear();
        dfs(root, -1, 0);

        int m = (int)euler.size();
        lg.assign(m + 1, 0);
        for (int i = 2; i <= m; i++) lg[i] = lg[i / 2] + 1;

        int K = lg[m] + 1;
        st.assign(K, vector<int>(m));
        for (int i = 0; i < m; i++) st[0][i] = i;

        for (int k = 1; k < K; k++) {
            int len = 1 << k;
            int half = len >> 1;
            for (int i = 0; i + len <= m; i++) {
                int a = st[k - 1][i];
                int b = st[k - 1][i + half];
                st[k][i] = (depthEuler[a] < depthEuler[b] ? a : b);
            }
        }
    }

    int lca(int u, int v) const {
        int l = first[u], r = first[v];
        if (l > r) swap(l, r);
        int k = lg[r - l + 1];
        int a = st[k][l];
        int b = st[k][r - (1 << k) + 1];
        return euler[depthEuler[a] < depthEuler[b] ? a : b];
    }

    int dist(int u, int v) const {
        int w = lca(u, v);
        return depthNode[u] + depthNode[v] - 2 * depthNode[w];
    }
};

// Example of use:
// LCAEulerTourRMQ lca(n);
// for each edge(u,v): lca.addEdge(u,v);
// lca.build(0);
// int w = lca.lca(u, v);
// int d = lca.dist(u, v);
