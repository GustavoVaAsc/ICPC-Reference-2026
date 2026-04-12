// Range Update - Range Query (1-based indexing)
struct FenwickRURQ {
    int n;
    std::vector<int> B1, B2;
    
    FenwickRURQ(int size) : n(size + 1), B1(size + 2), B2(size + 2) {}
    
    // Add val to range [l, r] (1-based)
    void range_add(int l, int r, int val) {
        add(B1, l, val);
        add(B1, r + 1, -val);
        add(B2, l, val * (l - 1));
        add(B2, r + 1, -val * r);
    }
    
    // Get sum of range [l, r] (1-based)
    int range_sum(int l, int r) {
        return prefix_sum(r) - prefix_sum(l - 1);
    }

private:
    void add(std::vector<int>& b, int idx, int val) {
        for(; idx < n; idx += idx & -idx)
            b[idx] += val;
    }
    
    int sum(const std::vector<int>& b, int idx) {
        int total = 0;
        for(; idx > 0; idx -= idx & -idx)
            total += b[idx];
        return total;
    }
    
    int prefix_sum(int idx) {
        return sum(B1, idx) * idx - sum(B2, idx);
    }
};