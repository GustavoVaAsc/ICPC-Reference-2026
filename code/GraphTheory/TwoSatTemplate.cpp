// 2-SAT (clean template)
// Main use cases:
// 1) Constraints of the form (a OR b), where literals are variables or negations.
// 2) Scheduling/selection with binary choices and incompatibilities.
// 3) Build implications and solve via SCC in O((N + M)).

struct TwoSatTemplate {
    int n;
    vector<vector<int>> g, rg;
    vector<int> comp, order, assignment;
    vector<char> used;

    explicit TwoSatTemplate(int n_) : n(n_), g(2 * n), rg(2 * n) {}

    int var(int x, bool isTrue) {
        return 2 * x ^ (isTrue ? 0 : 1);
    }

    int neg(int x) {
        return x ^ 1;
    }

    void addImplication(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    // Clause: (x = xVal) OR (y = yVal)
    void addOr(int x, bool xVal, int y, bool yVal) {
        int a = var(x, xVal);
        int b = var(y, yVal);
        addImplication(neg(a), b);
        addImplication(neg(b), a);
    }

    // Force variable x to value xVal
    void forceVar(int x, bool xVal) {
        int a = var(x, xVal);
        addImplication(neg(a), a);
    }

    void dfs1(int v) {
        used[v] = 1;
        for (int to : g[v]) if (!used[to]) dfs1(to);
        order.push_back(v);
    }

    void dfs2(int v, int c) {
        comp[v] = c;
        for (int to : rg[v]) if (comp[to] == -1) dfs2(to, c);
    }

    bool satisfiable() {
        int N = 2 * n;
        used.assign(N, 0);
        order.clear();

        for (int i = 0; i < N; i++) if (!used[i]) dfs1(i);

        comp.assign(N, -1);
        int j = 0;
        for (int i = N - 1; i >= 0; i--) {
            int v = order[i];
            if (comp[v] == -1) dfs2(v, j++);
        }

        assignment.assign(n, 0);
        for (int x = 0; x < n; x++) {
            if (comp[2 * x] == comp[2 * x + 1]) return false;
            assignment[x] = comp[2 * x] > comp[2 * x + 1];
        }
        return true;
    }
};

// Example of use:
// TwoSatTemplate ts(nVars);
// ts.addOr(0, true, 1, false); // (x0 OR !x1)
// ts.forceVar(2, true);         // x2 = true
// if (ts.satisfiable()) {
//     auto ans = ts.assignment;
// }
