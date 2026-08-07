// Odd-length manacher: d1[i] = radius of palindrome centered at i (including center)
vector<int> manacher_odd(const string& s) {
    int n = (int)s.size();
    vector<int> d(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 1 : min(d[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d[i] = k;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    return d;
}

// Even-length manacher: d2[i] = radius of palindrome centered between i-1 and i
vector<int> manacher_even(const string& s) {
    int n = (int)s.size();
    vector<int> d(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 0 : min(d[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d[i] = k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }
    return d;
}

// Returns array of max palindrome radius at each position.
// Result[i] = max palindrome half-length at position i (odd-length uses d1, even-length uses d2).
vector<int> manacher(string s) {
    string t;
    for (char c : s) {
        t += string("#") + c;
    }
    t += "#";
    vector<int> d1 = manacher_odd(t);
    vector<int> d2 = manacher_even(t);
    int n = (int)s.size();
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        int pos = 2 * i + 1; // position in transformed string
        int odd = d1[pos] - 1; // radius - 1 = original odd palindrome half-length contribution
        int even = 0;
        if (pos - 1 >= 0) even = d2[pos - 1]; // even palindrome radius at same center
        res[i] = max(odd, even);
    }
    return res;
}