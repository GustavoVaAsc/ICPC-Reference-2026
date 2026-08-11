// Mo's Algorithm for offline range query processing
// Time: O((N + Q) * sqrt(N))
// Based on KACTL: https://github.com/kth-competitive-programming/kactl

#pragma once

#include <bits/stdc++.h>
using namespace std;

// Mo's Algorithm for offline range query processing.
// T: answer/value type
// Add/Remove: functors or lambdas with operator(T) or add(T)/remove(T) methods
template <typename T>
struct MoQueries {
    struct Query {
        int l, r, idx;
    };

    vector<Query> queries;
    int n;

    explicit MoQueries(int n = 0) : n(n) {}

    void add_query(int l, int r) {
        queries.push_back({l, r, (int)queries.size()});
    }

    // Solve using provided add/remove/get operations
    // Operations can be lambdas or functor objects with operator()
    // add(x): add element x to current range
    // remove(x): remove element x from current range
    // get(): return current answer of type T
    template <typename Array, typename Add, typename Remove, typename Get>
    vector<T> solve(const Array& a, Add add, Remove remove, Get get) {
        int q = queries.size();
        int blk = static_cast<int>(sqrt(n));

        sort(queries.begin(), queries.end(), [&](const Query& i, const Query& j) {
            int bi = i.l / blk;
            int bj = j.l / blk;
            if (bi != bj) return bi < bj;
            // Alternate sorting direction per block to reduce pointer movement
            return (bi & 1) ? i.r > j.r : i.r < j.r;
        });

        vector<T> res(q);
        int L = 0, R = 0;

        for (const auto& qu : queries) {
            while (L > qu.l) add(a[--L]);
            while (R < qu.r) add(a[R++]);
            while (L < qu.l) remove(a[L++]);
            while (R > qu.r) remove(a[--R]);
            res[qu.idx] = get();
        }
        return res;
    }
};