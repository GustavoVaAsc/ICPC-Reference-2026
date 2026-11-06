// Mo's Algorithm (offline range queries)
// Main use cases:
// 1) Range queries on static arrays where merge is hard (distinct count, frequency-based stats).
// 2) Query type supports add/remove in O(1) or O(log V).
// Complexity: O((N + Q) * sqrt(N) * update_cost).

struct MoQuery {
    int l, r, idx;
};

struct MoAlgorithm {
    int n, block;
    vector<MoQuery> queries;

    explicit MoAlgorithm(int _n) : n(_n), block(max(1, (int)sqrt(_n))) {}

    void addQuery(int l, int r, int idx) {
        queries.push_back({l, r, idx});
    }

    vector<int> process(const vector<int>& a) {
        sort(queries.begin(), queries.end(), [&](const MoQuery& A, const MoQuery& B) {
            int blockA = A.l / block;
            int blockB = B.l / block;
            if (blockA != blockB) return blockA < blockB;
            // Small optimization: alternating order by block
            if (blockA & 1) return A.r > B.r;
            return A.r < B.r;
        });

        // Example payload: number of distinct values in [l, r].
        // If values are large, coordinate-compress first.
        int maxVal = 0;
        for (int x : a) maxVal = max(maxVal, x);
        vector<int> freq(maxVal + 1, 0);
        vector<int> ans((int)queries.size());

        int curL = 0, curR = -1;
        int distinct = 0;

        auto add = [&](int pos) {
            if (++freq[a[pos]] == 1) distinct++;
        };

        auto remove = [&](int pos) {
            if (--freq[a[pos]] == 0) distinct--;
        };

        for (const auto& q : queries) {
            while (curL > q.l) add(--curL);
            while (curR < q.r) add(++curR);
            while (curL < q.l) remove(curL++);
            while (curR > q.r) remove(curR--);
            ans[q.idx] = distinct;
        }

        return ans;
    }
};

// Example of use:
// vector<int> a = {1, 2, 1, 3, 2, 2, 4};
// vector<pair<int,int>> qs = {{0, 3}, {2, 6}};
// MoAlgorithm mo((int)a.size());
// for (int i = 0; i < (int)qs.size(); i++) mo.addQuery(qs[i].first, qs[i].second, i);
// vector<int> ans = mo.process(a); // answers distinct count for each query
