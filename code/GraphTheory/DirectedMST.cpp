using ll = long long;

// Directed MST / Minimum Arborescence (Chu-Liu / Edmonds)
// Main use cases:
// 1) Minimum-cost rooted directed spanning tree.
// 2) Problems asking minimum arborescence from fixed root.
// Returns -1 if some node is unreachable from root in any arborescence.

struct DMSTEdge {
    int u, v;
    ll w;
};

ll directedMST(int n, int root, vector<DMSTEdge> edges) {
    const ll INF = (ll)4e18;
    ll ans = 0;

    while (true) {
        vector<ll> in(n, INF);
        vector<int> pre(n, -1);

        for (auto &e : edges) {
            if (e.u != e.v && e.w < in[e.v]) {
                in[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }

        in[root] = 0;
        for (int i = 0; i < n; i++) {
            if (in[i] == INF) return -1; // unreachable node
        }

        int cntCycle = 0;
        vector<int> id(n, -1), vis(n, -1);

        for (int i = 0; i < n; i++) {
            ans += in[i];
            int v = i;
            while (vis[v] != i && id[v] == -1 && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            if (v != root && id[v] == -1) {
                for (int u = pre[v]; u != v; u = pre[u]) id[u] = cntCycle;
                id[v] = cntCycle++;
            }
        }

        if (cntCycle == 0) break;
        for (int i = 0; i < n; i++) if (id[i] == -1) id[i] = cntCycle++;

        vector<DMSTEdge> newEdges;
        newEdges.reserve(edges.size());
        for (auto &e : edges) {
            int u = id[e.u], v = id[e.v];
            ll w = e.w;
            if (u != v) w -= in[e.v];
            newEdges.push_back({u, v, w});
        }

        root = id[root];
        n = cntCycle;
        edges.swap(newEdges);
    }

    return ans;
}

// Example of use:
// vector<DMSTEdge> edges = {{u,v,w}, ...};
// ll cost = directedMST(n, root, edges);
// if (cost == -1) -> no arborescence exists.
