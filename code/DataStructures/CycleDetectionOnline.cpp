class CycleDetectionDSU {
    vector<int> parent;
    vector<int> size;

public:
    CycleDetectionDSU(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    // Returns true if adding edge u-v creates a cycle
    bool add_edge(int u, int v) {
        int u_root = find(u);
        int v_root = find(v);
        if (u_root == v_root) return true;
        
        if (size[u_root] < size[v_root]) swap(u_root, v_root);
        parent[v_root] = u_root;
        size[u_root] += size[v_root];
        return false;
    }
};