struct Edge {
    int u, v, w;
    bool operator<(Edge const& other) {
        return w < other.w;
    }
};
 
class DisjointSets {
private:
    vector<int> parents;
    vector<int> rank; // Use rank instead of size
 
public:
    DisjointSets(int size) : parents(size), rank(size, 0) {
        for (int i = 0; i < size; i++) parents[i] = i;
    }
 
    int find(int x) {
        if (parents[x] != x) parents[x] = find(parents[x]);
        return parents[x];
    }
 
    bool unite(int x, int y) {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root) return false;
 
        if (rank[x_root] < rank[y_root]) swap(x_root, y_root);
        parents[y_root] = x_root;
        if (rank[x_root] == rank[y_root]) rank[x_root]++;
        return true;
    }
};
 
 
int kruskal(int n, vector<Edge> &edges, vector<Edge> &ans){
    ll cost = 0;
    int ed_cnt = 0;
    DisjointSets dsu(n);
    sort(edges.begin(), edges.end());

    for(Edge e : edges){
        if(dsu.unite(e.u, e.v)){
            ans.push_back(e);
            cost += e.w;
            ed_cnt++;
        }
    }

    if (ed_cnt != n - 1) return -1;
    return cost;
}
 