// Z-Algorithm
vector<int> z_function(string s) {
    int n = s.length();
    vector<int> z(n);
    int l = 0, r = 0;
    
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

// Pattern matching using Z-algorithm
vector<int> patternMatch(string text, string pattern) {
    string combined = pattern + "$" + text;
    vector<int> z = z_function(combined);
    vector<int> matches;
    int m = pattern.length();
    
    for (int i = m + 1; i < combined.length(); i++) {
        if (z[i] == m) {
            matches.push_back(i - m - 1);
        }
    }
    return matches;
}
