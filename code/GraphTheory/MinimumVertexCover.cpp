// Minimum Vertex Cover in a bipartite graph (Konig's theorem).
// Requires maximum matching (matchL, matchR). 0-indexed.
// Returns (coverLeft, coverRight) as lists of vertex indices.
// Not for general graphs (NP-hard).

pair<vector<int>, vector<int>> minVertexCoverBipartite(
    const vector<vector<int>> &g,
    const vector<int> &matchL,
    const vector<int> &matchR
) {
    int nL = (int)g.size();
    int nR = (int)matchR.size();
    vector<int> visL(nL, 0), visR(nR, 0);
    queue<int> q;

    for (int u = 0; u < nL; u++) {
        if (matchL[u] == -1) {
            visL[u] = 1;
            q.push(u);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (matchL[u] == v) continue; // only traverse non-matching edges
            if (!visR[v]) {
                visR[v] = 1;
                int u2 = matchR[v];
                if (u2 != -1 && !visL[u2]) {
                    visL[u2] = 1;
                    q.push(u2);
                }
            }
        }
    }

    vector<int> coverL, coverR;
    for (int u = 0; u < nL; u++) if (!visL[u]) coverL.push_back(u);
    for (int v = 0; v < nR; v++) if (visR[v]) coverR.push_back(v);
    return {coverL, coverR};
}

// Example of use with Hopcroft-Karp:
// HopcroftKarp hk(nL, nR); ... hk.maxMatching();
// auto cover = minVertexCoverBipartite(hk.g, hk.matchL, hk.matchR);
