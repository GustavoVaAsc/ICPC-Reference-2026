#include <bits/stdc++.h>
using namespace std;

// Hopcroft-Karp: Maximum bipartite matching in O(E * sqrt(V))
// adj[i] contains right-side neighbors of left vertex i (0-indexed)
// Returns size of maximum matching.
// Left vertices: 0..n_l-1, Right vertices: 0..n_r-1

int hopcroft_karp(int n_l, int n_r, const vector<vector<int>>& adj) {
    const int INF = 1e9;

    vector<int> pair_l(n_l, -1), pair_r(n_r, -1), dist(n_l);

    auto bfs = [&]() -> bool {
        queue<int> q;
        for (int u = 0; u < n_l; ++u) {
            if (pair_l[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }

        bool reachable_free = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int pu = pair_r[v];
                if (pu != -1 && dist[pu] == INF) {
                    dist[pu] = dist[u] + 1;
                    q.push(pu);
                }
                if (pu == -1) {
                    reachable_free = true;
                }
            }
        }
        return reachable_free;
    };

    function<bool(int)> dfs = [&](int u) -> bool {
        for (int v : adj[u]) {
            int pu = pair_r[v];
            if (pu == -1 || (dist[pu] == dist[u] + 1 && dfs(pu))) {
                pair_l[u] = v;
                pair_r[v] = u;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    };

    int matching = 0;
    while (bfs()) {
        for (int u = 0; u < n_l; ++u) {
            if (pair_l[u] == -1 && dfs(u))
                ++matching;
        }
    }
    return matching;
}
