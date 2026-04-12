// Old implementation, use global variables.

const int MAX = 2e5+3;
 
#define INF LLONG_MAX 
typedef pair<ll, ll> pll;
 
vector<ll> dijkstra(int n, int source, vector<vector<pll>> &adj) {
    vector<ll> dist(n, INF);
    priority_queue<pll, vector<pll>, greater<pll>> pq; 
    dist[source] = 0;
    pq.push({0, source}); 
 
    while (!pq.empty()) {
        ll d = pq.top().first; 
        ll u = pq.top().second; 
        pq.pop();
 
        if (d > dist[u]) continue;
 
        for (auto &edge : adj[u]) {
            ll v = edge.first;
            ll weight = edge.second; 
 
            if (dist[u] + weight < dist[v]) { 
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v}); 
            }
        }
    }
 
    return dist;
}
