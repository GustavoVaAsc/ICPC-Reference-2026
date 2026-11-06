// Wavelet Tree (static array)
// Main use cases:
// 1) k-th smallest in subarray [l, r]
// 2) count numbers <= x in [l, r]
// 3) frequency of value x in [l, r]
// Complexity: O(log Sigma) per query.

struct WaveletTree {
    int lo, hi;
    WaveletTree *l = nullptr, *r = nullptr;
    vector<int> pref; // pref[i] = count sent to left among first i elements

    WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y) {
        lo = x;
        hi = y;
        if (from >= to || lo == hi) return;

        int mid = (lo + hi) >> 1;
        auto goesLeft = [mid](int v) { return v <= mid; };

        pref.reserve((to - from) + 1);
        pref.push_back(0);
        for (auto it = from; it != to; ++it) pref.push_back(pref.back() + (goesLeft(*it) ? 1 : 0));

        auto pivot = stable_partition(from, to, goesLeft);
        if (from < pivot) l = new WaveletTree(from, pivot, lo, mid);
        if (pivot < to) r = new WaveletTree(pivot, to, mid + 1, hi);
    }

    // kth smallest in [lq, rq], 1-indexed k, and 1-indexed query bounds.
    int kth(int lq, int rq, int k) const {
        if (lq > rq) return -1;
        if (lo == hi) return lo;

        int inLeft = pref[rq] - pref[lq - 1];
        if (k <= inLeft) {
            int nl = pref[lq - 1] + 1;
            int nr = pref[rq];
            return this->l->kth(nl, nr, k);
        }

        int nl = lq - pref[lq - 1];
        int nr = rq - pref[rq];
        return this->r->kth(nl, nr, k - inLeft);
    }

    // Count of values <= x in [lq, rq], 1-indexed bounds.
    int LTE(int lq, int rq, int x) const {
        if (lq > rq || x < lo) return 0;
        if (hi <= x) return rq - lq + 1;

        int leftPart = 0, rightPart = 0;
        if (l) leftPart = l->LTE(pref[lq - 1] + 1, pref[rq], x);
        if (r) rightPart = r->LTE(lq - pref[lq - 1], rq - pref[rq], x);
        return leftPart + rightPart;
    }

    // Frequency of value x in [lq, rq], 1-indexed bounds.
    int countEq(int lq, int rq, int x) const {
        if (lq > rq || x < lo || x > hi) return 0;
        if (lo == hi) return rq - lq + 1;

        int mid = (lo + hi) >> 1;
        if (x <= mid) {
            if (!l) return 0;
            return l->countEq(pref[lq - 1] + 1, pref[rq], x);
        }

        if (!r) return 0;
        return r->countEq(lq - pref[lq - 1], rq - pref[rq], x);
    }
};

// Example of use:
// vector<int> a = ...;  // values in range [mn, mx]
// WaveletTree wt(a.begin(), a.end(), mn, mx);
// int kth = wt.kth(l+1, r+1, k);
// int cnt = wt.LTE(l+1, r+1, x);
