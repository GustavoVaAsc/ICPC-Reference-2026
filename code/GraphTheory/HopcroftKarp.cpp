// Hopcroft-Karp (maximum bipartite matching)
// Main use cases:
// 1) Maximum matching in unweighted bipartite graph.
// 2) Minimum vertex cover in bipartite graphs (via Konig theorem after matching).
// Complexity: O(E * sqrt(V)).
// The BFS computes the length of the shortest augmenting path (distNil) and the DFS only
// augments along paths of that exact length, so a phase finds a maximal set of vertex-disjoint
// shortest augmenting paths and the number of phases is O(sqrt(V)).

struct HopcroftKarp {
    static const int INF_DIST = 1000000000;

    int nL, nR;
    vector<vector<int>> g;
    vector<int> dist, matchL, matchR;
    int distNil; // BFS distance of a free right vertex (length of shortest augmenting path)

    HopcroftKarp(int leftSize, int rightSize)
        : nL(leftSize), nR(rightSize), g(leftSize), dist(leftSize),
          matchL(leftSize, -1), matchR(rightSize, -1), distNil(INF_DIST) {}

    void addEdge(int uLeft, int vRight) {
        g[uLeft].push_back(vRight);
    }

    // Builds the level graph and computes distNil = length of the shortest augmenting path.
    bool bfs() {
        queue<int> q;
        for (int u = 0; u < nL; u++) {
            if (matchL[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF_DIST;
            }
        }
        distNil = INF_DIST;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] >= distNil) continue; // do not explore beyond the shortest path length
            for (int v : g[u]) {
                int u2 = matchR[v];
                if (u2 == -1) {
                    distNil = dist[u] + 1; // free right vertex at this level
                } else if (dist[u2] == INF_DIST) {
                    dist[u2] = dist[u] + 1;
                    q.push(u2);
                }
            }
        }
        return distNil != INF_DIST;
    }

    // Augments along a shortest augmenting path only.
    bool dfs(int u) {
        for (int v : g[u]) {
            int u2 = matchR[v];
            if (u2 == -1) {
                if (dist[u] + 1 != distNil) continue;
            } else {
                if (dist[u2] != dist[u] + 1 || !dfs(u2)) continue;
            }
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
        dist[u] = INF_DIST;
        return false;
    }

    int maxMatching() {
        // Reset the matching state so that the call is idempotent: it always recomputes a maximum
        // matching from scratch, and bfs() re-initialises dist for every left vertex each phase.
        fill(matchL.begin(), matchL.end(), -1);
        fill(matchR.begin(), matchR.end(), -1);
        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < nL; u++) {
                if (matchL[u] == -1 && dfs(u)) matching++;
            }
        }
        return matching;
    }
};

// Example of use:
// HopcroftKarp hk(nLeft, nRight);
// hk.addEdge(u, v);
// int maxMatch = hk.maxMatching(); // may be called repeatedly; each call recomputes from scratch
