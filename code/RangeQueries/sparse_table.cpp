// Sparse Table for Range Minimum Query
class SparseTable {
    vector<vector<int>> table;
    vector<int> log;
    int n;
    
public:
    SparseTable(vector<int>& arr) {
        n = arr.size();
        int maxLog = log2(n) + 1;
        table.assign(n, vector<int>(maxLog));
        log.assign(n + 1, 0);
        
        // Precompute logarithms
        for (int i = 2; i <= n; i++) {
            log[i] = log[i/2] + 1;
        }
        
        // Build sparse table
        for (int i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }
        
        for (int j = 1; j < maxLog; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[i][j] = min(table[i][j-1], 
                                  table[i + (1 << (j-1))][j-1]);
            }
        }
    }
    
    int query(int l, int r) {
        int j = log[r - l + 1];
        return min(table[l][j], table[r - (1 << j) + 1][j]);
    }
};
