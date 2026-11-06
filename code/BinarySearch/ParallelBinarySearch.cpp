using ll = long long;

// Parallel Binary Search (PBS) template
// Main use cases:
// 1) Offline "first time condition becomes true" queries.
// 2) Monotone answer over time/operations index.
// 3) Common with Fenwick/segment tree + batch checking.

struct Fenwick {
    int n;
    vector<ll> bit;

    explicit Fenwick(int n_) : n(n_), bit(n_ + 1, 0) {}

    void add(int idx, ll val) {
        for (++idx; idx <= n; idx += idx & -idx) bit[idx] += val;
    }

    ll sumPrefix(int idx) const {
        ll s = 0;
        for (++idx; idx > 0; idx -= idx & -idx) s += bit[idx];
        return s;
    }
};

// Example setting:
// - updates[i] adds delta at position pos (0-indexed)
// - each query asks earliest update index t such that prefix(pos) >= need
struct PBSExample {
    struct Update { int pos; ll delta; };
    struct Query { int pos; ll need; };

    vector<Update> updates;
    vector<Query> queries;

    // Returns earliest index in [0..m-1], or -1 if never satisfied.
    vector<int> earliestSatisfying(int n) {
        int q = (int)queries.size();
        int m = (int)updates.size();

        vector<int> lo(q, 0), hi(q, m - 1), ans(q, -1);
        vector<char> alive(q, 1);

        while (true) {
            bool any = false;
            vector<vector<int>> bucket(m);

            for (int i = 0; i < q; i++) {
                if (!alive[i]) continue;
                if (lo[i] > hi[i]) {
                    alive[i] = 0;
                    continue;
                }
                any = true;
                int mid = (lo[i] + hi[i]) >> 1;
                bucket[mid].push_back(i);
            }
            if (!any) break;

            Fenwick fw(n);
            for (int i = 0; i < m; i++) {
                fw.add(updates[i].pos, updates[i].delta);

                for (int qid : bucket[i]) {
                    ll cur = fw.sumPrefix(queries[qid].pos);
                    if (cur >= queries[qid].need) {
                        ans[qid] = i;
                        hi[qid] = i - 1;
                    } else {
                        lo[qid] = i + 1;
                    }
                }
            }
        }

        return ans;
    }
};

// Contest note:
// For range updates or richer checks, replace Fenwick logic with your DS.
