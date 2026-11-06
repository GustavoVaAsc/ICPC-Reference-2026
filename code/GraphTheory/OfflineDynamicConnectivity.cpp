// Offline Dynamic Connectivity with rollback DSU + segment tree on time.
// Main use cases:
// 1) Edge add/remove and connectivity queries in offline setting.
// 2) Dynamic graph connectivity where online fully dynamic is too hard.
// Complexity: O((Q log Q) * alpha(N)) amortized with rollback DSU.

struct RollbackDSU {
    vector<int> p, sz;
    vector<pair<int, int>> stk; // (childRoot, sizeOfParentBefore)
    int comps;

    explicit RollbackDSU(int n) : p(n), sz(n, 1), comps(n) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        while (x != p[x]) x = p[x];
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            stk.push_back({-1, -1});
            return false;
        }
        if (sz[a] < sz[b]) swap(a, b);
        stk.push_back({b, sz[a]});
        p[b] = a;
        sz[a] += sz[b];
        comps--;
        return true;
    }

    int snapshot() const { return (int)stk.size(); }

    void rollback(int snap) {
        while ((int)stk.size() > snap) {
            auto [b, oldSizeA] = stk.back();
            stk.pop_back();
            if (b == -1) continue;
            int a = p[b];
            p[b] = b;
            sz[a] = oldSizeA;
            comps++;
        }
    }
};

struct OfflineDynamicConnectivity {
    struct Edge {
        int u, v;
    };

    struct Query {
        int type; // 0: add, 1: remove, 2: ask(u,v)
        int u, v;
    };

    int n, q;
    vector<Query> queries;
    vector<vector<Edge>> seg;
    vector<int> answers;

    explicit OfflineDynamicConnectivity(int n_) : n(n_) {}

    static pair<int, int> normEdge(int u, int v) {
        if (u > v) swap(u, v);
        return {u, v};
    }

    void addQuery(int type, int u, int v) {
        queries.push_back({type, u, v});
    }

    void addSegEdge(int node, int l, int r, int ql, int qr, Edge e) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            seg[node].push_back(e);
            return;
        }
        int mid = (l + r) >> 1;
        addSegEdge(node << 1, l, mid, ql, qr, e);
        addSegEdge(node << 1 | 1, mid + 1, r, ql, qr, e);
    }

    void dfs(int node, int l, int r, RollbackDSU &dsu) {
        int snap = dsu.snapshot();
        for (auto &e : seg[node]) dsu.unite(e.u, e.v);

        if (l == r) {
            if (queries[l].type == 2) {
                answers.push_back(dsu.find(queries[l].u) == dsu.find(queries[l].v));
            }
        } else {
            int mid = (l + r) >> 1;
            dfs(node << 1, l, mid, dsu);
            dfs(node << 1 | 1, mid + 1, r, dsu);
        }

        dsu.rollback(snap);
    }

    vector<int> solve() {
        q = (int)queries.size();
        seg.assign(4 * max(1, q), {});
        answers.clear();

        map<pair<int, int>, int> start;
        for (int i = 0; i < q; i++) {
            auto [u, v] = normEdge(queries[i].u, queries[i].v);
            if (queries[i].type == 0) {
                start[{u, v}] = i;
            } else if (queries[i].type == 1) {
                auto it = start.find({u, v});
                if (it != start.end()) {
                    addSegEdge(1, 0, q - 1, it->second, i - 1, {u, v});
                    start.erase(it);
                }
            }
        }

        for (auto &it : start) {
            addSegEdge(1, 0, q - 1, it.second, q - 1, {it.first.first, it.first.second});
        }

        RollbackDSU dsu(n);
        if (q > 0) dfs(1, 0, q - 1, dsu);
        return answers;
    }
};

// Example usage:
// type 0(u,v): add edge
// type 1(u,v): remove edge
// type 2(u,v): ask if u and v are connected
