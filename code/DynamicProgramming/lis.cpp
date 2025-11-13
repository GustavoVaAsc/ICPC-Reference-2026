// Longest Increasing Subsequence in O(n log n)
int lis(vector<int>& arr) {
    vector<int> dp;
    
    for (int x : arr) {
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end()) {
            dp.push_back(x);
        } else {
            *it = x;
        }
    }
    
    return dp.size();
}

// If you need to reconstruct the sequence
vector<int> lisSequence(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp, parent(n, -1), indices;
    
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), arr[i]);
        int pos = it - dp.begin();
        
        if (it == dp.end()) {
            dp.push_back(arr[i]);
            indices.push_back(i);
        } else {
            *it = arr[i];
            indices[pos] = i;
        }
        
        if (pos > 0) {
            parent[i] = indices[pos - 1];
        }
    }
    
    vector<int> result;
    int curr = indices.back();
    while (curr != -1) {
        result.push_back(arr[curr]);
        curr = parent[curr];
    }
    reverse(result.begin(), result.end());
    return result;
}
