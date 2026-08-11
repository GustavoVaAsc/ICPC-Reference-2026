// Sqrt Decomposition -- range sum queries & point updates in O((N+Q)*sqrt(N))
#include <vector>
#include <cmath>

using ll = long long;

template <typename T>
class SqrtDecomp {
    int n, sz;
    std::vector<T> a;
    std::vector<ll> block;

public:
    SqrtDecomp(const std::vector<T>& arr) {
        n = (int)arr.size();
        sz = (int)std::sqrt(n) + 1;
        a = arr;
        block.assign((n + sz - 1) / sz, 0);
        for (int i = 0; i < n; i++)
            block[i / sz] += arr[i];
    }

    // point update: set a[i] = val
    void update(int i, T val) {
        block[i / sz] += val - a[i];
        a[i] = val;
    }

    // inclusive range query [l, r]
    ll query(int l, int r) const {
        ll res = 0;
        int start = l / sz, end = r / sz;
        if (start == end) {
            for (int i = l; i <= r; i++)
                res += a[i];
            return res;
        }
        // left partial block
        for (int i = l; i < (start + 1) * sz; i++)
            res += a[i];
        // full blocks
        for (int b = start + 1; b < end; b++)
            res += block[b];
        // right partial block
        for (int i = end * sz; i <= r; i++)
            res += a[i];
        return res;
    }
};
