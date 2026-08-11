#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e17;

vector<ll> dijkstra(int n, int source, const vector<vector<pair<int,ll>>>& adj, const vector<ll>& h) {
    vector<ll> dist(n, INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            ll reweighted = w + h[u] - h[v];
            if (dist[u] + reweighted < dist[v]) {
                dist[v] = dist[u] + reweighted;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

vector<vector<ll>> johnson(int n, const vector<vector<pair<int,ll>>>& adj) {
    vector<vector<pair<int,ll>>> aug = adj;
    for (int i = 0; i < n; i++) {
        aug[i].push_back({n, 0});
    }

    vector<ll> dist(n + 1, INF);
    dist[n] = 0;
    for (int i = 0; i < n; i++) {
        bool updated = false;
        for (int u = 0; u <= n; u++) {
            if (dist[u] == INF) continue;
            for (auto [v, w] : aug[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }

    vector<ll> h(n);
    for (int i = 0; i < n; i++) h[i] = (dist[i] == INF) ? 0 : dist[i];

    vector<vector<ll>> result(n, vector<ll>(n, INF));
    for (int s = 0; s < n; s++) {
        vector<ll> d = dijkstra(n, s, adj, h);
        for (int t = 0; t < n; t++) {
            if (d[t] != INF) {
                result[s][t] = d[t] - h[s] + h[t];
            }
        }
    }
    return result;
}
