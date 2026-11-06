// Hopcroft-Karp (maximum bipartite matching)
// Main use cases:
// 1) Maximum matching in unweighted bipartite graph.
// 2) Minimum vertex cover in bipartite graphs (via Konig theorem after matching).
// Complexity: O(E * sqrt(V)).

struct HopcroftKarp {
    int nL, nR;
    vector<vector<int>> g;
    vector<int> dist, matchL, matchR;

    HopcroftKarp(int leftSize, int rightSize)
        : nL(leftSize), nR(rightSize), g(leftSize), dist(leftSize),
          matchL(leftSize, -1), matchR(rightSize, -1) {}

    void addEdge(int uLeft, int vRight) {
        g[uLeft].push_back(vRight);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < nL; u++) {
            if (matchL[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }

        bool foundAugPath = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                int u2 = matchR[v];
                if (u2 == -1) {
                    foundAugPath = true;
                } else if (dist[u2] == -1) {
                    dist[u2] = dist[u] + 1;
                    q.push(u2);
                }
            }
        }
        return foundAugPath;
    }

    bool dfs(int u) {
        for (int v : g[u]) {
            int u2 = matchR[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int maxMatching() {
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
// int maxMatch = hk.maxMatching();
