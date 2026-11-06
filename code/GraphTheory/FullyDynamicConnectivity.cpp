// Fully Dynamic Connectivity (general graphs, simple replacement search).
// Requires LinkCutTree (code/Trees/LinkCutTree.cpp).
// Insert/query: O(log n). Delete: O(size of smaller tree component + edges scanned).

struct FullyDynamicConnectivity {
    struct Edge {
        int u, v;
        bool isTree;
        bool alive;
    };

    int n;
    LinkCutTree lct;
    vector<vector<int>> treeAdj;
    vector<vector<int>> nonTreeAdj;
    vector<Edge> edges;

    FullyDynamicConnectivity(int n = 0)
        : n(n), lct(n), treeAdj(n + 1), nonTreeAdj(n + 1) {}

    int addEdge(int u, int v) {
        int id = (int)edges.size();
        edges.push_back({u, v, false, true});
        if (!lct.connected(u, v)) {
            lct.link(u, v);
            edges[id].isTree = true;
            treeAdj[u].push_back(id);
            treeAdj[v].push_back(id);
        } else {
            nonTreeAdj[u].push_back(id);
            nonTreeAdj[v].push_back(id);
        }
        return id;
    }

    void removeEdge(int id) {
        if (id < 0 || id >= (int)edges.size()) return;
        if (!edges[id].alive) return;
        edges[id].alive = false;
        if (edges[id].isTree) removeTreeEdge(id);
    }

    bool connected(int u, int v) {
        return lct.connected(u, v);
    }

    vector<int> getComponent(int start) {
        vector<int> comp;
        vector<int> vis(n + 1, 0);
        queue<int> q;
        vis[start] = 1;
        q.push(start);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            comp.push_back(u);
            for (int id : treeAdj[u]) {
                const Edge &e = edges[id];
                if (!e.alive || !e.isTree) continue;
                int v = e.u ^ e.v ^ u;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        return comp;
    }

    void removeTreeEdge(int id) {
        Edge &e = edges[id];
        int u = e.u, v = e.v;
        e.isTree = false;
        lct.cut(u, v);

        vector<int> compU = getComponent(u);
        vector<int> compV = getComponent(v);
        vector<int> *comp = &compU;
        if (compV.size() < compU.size()) comp = &compV;

        vector<int> inComp(n + 1, 0);
        for (int x : *comp) inComp[x] = 1;

        for (int x : *comp) {
            for (int id2 : nonTreeAdj[x]) {
                Edge &e2 = edges[id2];
                if (!e2.alive || e2.isTree) continue;
                int y = e2.u ^ e2.v ^ x;
                if (inComp[y]) continue;
                e2.isTree = true;
                lct.link(e2.u, e2.v);
                treeAdj[e2.u].push_back(id2);
                treeAdj[e2.v].push_back(id2);
                return;
            }
        }
    }
};

// Example of use:
// FullyDynamicConnectivity dc(n);
// int id = dc.addEdge(u, v);
// bool ok = dc.connected(a, b);
// dc.removeEdge(id);
