#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll LINF = numeric_limits<ll>::max() / 4;

struct MCMFEdge {
    int to, rev;
    ll cap, cost;
};

struct MinCostMaxFlow {
    int n, s, t;
    ll flow_ = 0, cost_ = 0;
    vector<vector<MCMFEdge>> adj;
    vector<ll> pot, dist;
    vector<int> prevnode, prevedge;

    MinCostMaxFlow(int n, int s, int t) : n(n), s(s), t(t) {
        adj.assign(n, {});
        pot.resize(n, 0);
        dist.resize(n);
        prevnode.resize(n);
        prevedge.resize(n);
    }

    void add_edge(int from, int to, ll cap, ll cost) {
        MCMFEdge a{to, (int)adj[to].size(), cap, cost};
        MCMFEdge b{from, (int)adj[from].size(), 0, -cost};
        adj[from].push_back(a);
        adj[to].push_back(b);
    }

    bool dijkstra() {
        fill(dist.begin(), dist.end(), LINF);
        fill(prevnode.begin(), prevnode.end(), -1);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

        dist[s] = 0;
        pq.emplace(0, s);

        while (!pq.empty()) {
            auto [d, v] = pq.top();
            pq.pop();
            if (d != dist[v]) continue;
            for (int i = 0; i < (int)adj[v].size(); i++) {
                MCMFEdge &e = adj[v][i];
                if (e.cap <= 0) continue;
                ll ndist = dist[v] + e.cost + pot[v] - pot[e.to];
                if (ndist < dist[e.to]) {
                    dist[e.to] = ndist;
                    prevnode[e.to] = v;
                    prevedge[e.to] = i;
                    pq.emplace(ndist, e.to);
                }
            }
        }

        if (dist[t] == LINF) return false;

        for (int i = 0; i < n; i++) {
            if (dist[i] < LINF) pot[i] += dist[i];
        }

        return true;
    }

    void augment() {
        ll addflow = LINF;
        for (int v = t; v != s; v = prevnode[v]) {
            MCMFEdge &e = adj[prevnode[v]][prevedge[v]];
            addflow = min(addflow, e.cap);
        }

        for (int v = t; v != s; v = prevnode[v]) {
            MCMFEdge &e = adj[prevnode[v]][prevedge[v]];
            e.cap -= addflow;
            adj[e.to][e.rev].cap += addflow;
        }

        flow_ += addflow;
        cost_ += addflow * pot[t];
    }

    pair<ll, ll> min_cost_flow(int s, int t) {
        this->s = s;
        this->t = t;
        flow_ = 0;
        cost_ = 0;
        fill(pot.begin(), pot.end(), 0);

        while (dijkstra()) {
            augment();
        }
        return {flow_, cost_};
    }

    ll flow() const { return flow_; }
    ll cost() const { return cost_; }
};