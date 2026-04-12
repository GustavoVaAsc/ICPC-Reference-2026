// Suffix Array + LCP (Kasai)
struct SuffixArray {
    string s;
    vector<int> sa;    // Suffix array: indices of suffixes in sorted order
    vector<int> rank;  // rank[i] = position of suffix i in sa
    vector<int> lcp;   // lcp[i] = LCP(sa[i], sa[i-1]), lcp[0] = 0

    SuffixArray() {}
    explicit SuffixArray(const string& str) { build(str); }

    void build(const string& str) {
        s = str;
        int n = (int)s.size();
        sa.resize(n);
        rank.resize(n);

        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = s[i];
        }

        vector<int> tmp(n);
        for (int k = 1;; k <<= 1) {
            auto cmp = [&](int i, int j) {
                if (rank[i] != rank[j]) return rank[i] < rank[j];
                int ri = (i + k < n) ? rank[i + k] : -1;
                int rj = (j + k < n) ? rank[j + k] : -1;
                return ri < rj;
            };

            sort(sa.begin(), sa.end(), cmp);
            tmp[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            }

            rank = tmp;
            if (rank[sa[n - 1]] == n - 1) break;
        }

        buildLCP();
    }

    void buildLCP() {
        int n = (int)s.size();
        lcp.assign(n, 0);
        for (int i = 0; i < n; i++) rank[sa[i]] = i;

        int k = 0;
        for (int i = 0; i < n; i++) {
            if (rank[i] == 0) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[rank[i]] = k;
            if (k) k--;
        }
    }
};

// Example of use:
// Find the longest repeated substring in s.
string longestRepeatedSubstring(const string& s) {
    if (s.empty()) return "";
    SuffixArray sa(s);

    int bestLen = 0;
    int bestPos = 0;
    for (int i = 1; i < (int)sa.lcp.size(); i++) {
        if (sa.lcp[i] > bestLen) {
            bestLen = sa.lcp[i];
            bestPos = sa.sa[i];
        }
    }
    return s.substr(bestPos, bestLen);
}
