// Top Tree (path aggregate via edge nodes).
// Supports link/cut by edge id and path sum in O(log n) amortized.
// Works only on forests (no cycles).

struct TopTree {
    struct Node {
        int ch[2];
        int p;
        bool rev;
        long long val;
        long long sum;
        Node() : ch{0, 0}, p(0), rev(false), val(0), sum(0) {}
    };

    int n;
    int nextId;
    vector<Node> t;
    vector<int> edgeU, edgeV; // endpoints for edge nodes

    TopTree(int n = 0, int maxEdges = 0) { init(n, maxEdges); }

    void init(int n_, int maxEdges) {
        n = n_;
        nextId = n;
        t.assign(n + maxEdges + 5, Node());
        edgeU.assign(n + maxEdges + 5, 0);
        edgeV.assign(n + maxEdges + 5, 0);
    }

    bool isRoot(int x) const {
        int p = t[x].p;
        return p == 0 || (t[p].ch[0] != x && t[p].ch[1] != x);
    }

    void push(int x) {
        if (!x || !t[x].rev) return;
        swap(t[x].ch[0], t[x].ch[1]);
        int l = t[x].ch[0], r = t[x].ch[1];
        if (l) t[l].rev ^= 1;
        if (r) t[r].rev ^= 1;
        t[x].rev = false;
    }

    void pull(int x) {
        t[x].sum = t[t[x].ch[0]].sum + t[t[x].ch[1]].sum + t[x].val;
    }

    void rotate(int x) {
        int p = t[x].p;
        int g = t[p].p;
        push(p);
        push(x);
        int dir = (t[p].ch[1] == x);
        int b = t[x].ch[dir ^ 1];

        if (!isRoot(p)) {
            if (t[g].ch[0] == p) t[g].ch[0] = x;
            else if (t[g].ch[1] == p) t[g].ch[1] = x;
        }
        t[x].p = g;
        t[x].ch[dir ^ 1] = p;
        t[p].p = x;
        t[p].ch[dir] = b;
        if (b) t[b].p = p;

        pull(p);
        pull(x);
    }

    void splay(int x) {
        static vector<int> stk;
        stk.clear();
        int y = x;
        stk.push_back(y);
        while (!isRoot(y)) {
            y = t[y].p;
            stk.push_back(y);
        }
        for (int i = (int)stk.size() - 1; i >= 0; i--) push(stk[i]);

        while (!isRoot(x)) {
            int p = t[x].p;
            int g = t[p].p;
            if (!isRoot(p)) {
                if ((t[p].ch[0] == x) ^ (t[g].ch[0] == p)) rotate(x);
                else rotate(p);
            }
            rotate(x);
        }
        pull(x);
    }

    void access(int x) {
        int last = 0;
        for (int y = x; y; y = t[y].p) {
            splay(y);
            t[y].ch[1] = last;
            pull(y);
            last = y;
        }
        splay(x);
    }

    void makeRoot(int x) {
        access(x);
        t[x].rev ^= 1;
    }

    int findRoot(int x) {
        access(x);
        while (t[x].ch[0]) {
            push(x);
            x = t[x].ch[0];
        }
        splay(x);
        return x;
    }

    bool connected(int u, int v) {
        if (u == v) return true;
        return findRoot(u) == findRoot(v);
    }

    void cut(int u, int v) {
        makeRoot(u);
        access(v);
        if (t[v].ch[0] == u && t[u].ch[1] == 0) {
            t[v].ch[0] = 0;
            t[u].p = 0;
            pull(v);
        }
    }

    int addEdgeNode(int u, int v, long long w) {
        int e = ++nextId;
        t[e].val = w;
        pull(e);
        edgeU[e] = u;
        edgeV[e] = v;
        return e;
    }

    int linkEdge(int u, int v, long long w) {
        int e = addEdgeNode(u, v, w);
        makeRoot(u);
        makeRoot(v);
        t[u].p = e;
        t[v].p = e;
        pull(e);
        return e;
    }

    void cutEdge(int e) {
        int u = edgeU[e];
        int v = edgeV[e];
        if (u == 0 && v == 0) return;
        cut(u, e);
        cut(v, e);
        edgeU[e] = edgeV[e] = 0;
    }

    void setValue(int x, long long v) {
        access(x);
        t[x].val = v;
        pull(x);
    }

    long long pathSum(int u, int v) {
        makeRoot(u);
        access(v);
        return t[v].sum;
    }
};

// Example of use (edge weights):
// TopTree tt(n, maxEdges);
// int e = tt.linkEdge(u, v, w);
// long long sum = tt.pathSum(u, v);
// tt.cutEdge(e);
