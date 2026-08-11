/**
 * Push-Relabel Max-Flow (Highest-Label + Gap Relabeling)
 * Time: O(V^2 sqrt(E)) worst case, faster than Dinic on dense graphs
 * Based on KACTL PushRelabel.h
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX;

struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c;
    };

    int n;
    vector<vector<Edge>> g;
    vector<ll> ec;       // excess capacity
    vector<Edge*> cur;   // current edge pointer
    vector<vector<int>> hs;
    vector<int> H;

    PushRelabel(int n) : n(n), g(n), ec(n), cur(n), hs(2 * n), H(n) {}

    void add_edge(int u, int v, ll cap) {
        if (u == v) return;
        g[u].push_back({v, (int)g[v].size(), 0, cap});
        g[v].push_back({u, (int)g[u].size() - 1, 0, 0});
    }

    void addFlow(Edge& e, ll f) {
        Edge& back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f;
        e.c -= f;
        ec[e.dest] += f;
        back.f -= f;
        back.c += f;
        ec[back.dest] -= f;
    }

    ll max_flow(int s, int t) {
        int v = n;
        H[s] = v;
        ec[t] = 1;
        vector<int> co(2 * v);
        co[0] = v - 1;
        for (int i = 0; i < v; i++) cur[i] = g[i].data();

        for (Edge& e : g[s]) addFlow(e, e.c);

        for (int hi = 0;;) {
            while (hs[hi].empty()) if (hi-- == 0) return -ec[s];
            int u = hs[hi].back();
            hs[hi].pop_back();

            while (ec[u] > 0) {  // discharge u
                if (cur[u] == g[u].data() + (int)g[u].size()) {
                    H[u] = INT_MAX;
                    for (Edge& e : g[u])
                        if (e.c && H[u] > H[e.dest] + 1)
                            H[u] = H[e.dest] + 1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        for (int i = 0; i < v; i++)
                            if (hi < H[i] && H[i] < v)
                                --co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else
                    ++cur[u];
            }
        }
    }

    // Returns true if vertex is on the source side of min cut
    bool left_of_min_cut(int a) { return H[a] >= n; }
};
