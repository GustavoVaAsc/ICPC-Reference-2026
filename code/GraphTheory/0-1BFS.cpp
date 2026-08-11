#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> zero_one_bfs(int n, int src, const vector<vector<pair<int,int>>>& adj) {
    const ll INF = (ll)1e17;
    vector<ll> dist(n, INF);
    deque<int> dq;
    dist[src] = 0;
    dq.push_back(src);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }
    return dist;
}
