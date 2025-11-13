// Fenwick Tree (Binary Indexed Tree)
class FenwickTree {
    vector<long long> tree;
    int n;
    
public:
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}
    
    void update(int idx, int delta) {
        for (++idx; idx <= n; idx += idx & -idx) {
            tree[idx] += delta;
        }
    }
    
    long long query(int idx) {
        long long sum = 0;
        for (++idx; idx > 0; idx -= idx & -idx) {
            sum += tree[idx];
        }
        return sum;
    }
    
    long long query(int l, int r) {
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }
};
