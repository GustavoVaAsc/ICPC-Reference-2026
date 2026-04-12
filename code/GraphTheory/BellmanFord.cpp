const ll INF = 1e17;
const ll MIN_INF = (-1)*INF;
 
vector<ll> dist(MAX, INF);
 
struct Edge {
    int u, v;
    ll w;
};
 
void bellmanFord(int V, int E, vector<Edge>& edges, int start) {
    dist[start] = 0;
    vector<int> prev(V, -1);
 
    for (int i = 0; i < V-1; i++){
        for (int j = 0; j < E; j++){
            int u = edges[j].u;
            int v = edges[j].v;
            ll w = edges[j].w;
            if (dist[u] == INF) continue;
            dist[v] = min(dist[v], w+dist[u]);
            if (dist[v] > dist[u] + w){
                dist[v] = max(MIN_INF, dist[u] + w);
            }
        }
    }
 
    for (int i = 0; i < V-1; i++){
        for (int j = 0; j < E; j++){
            int u = edges[j].u;
            int v = edges[j].v;
            ll w = edges[j].w;
            if (dist[u] == INF) continue;
            dist[v] = max(MIN_INF,dist[v]);
            if (dist[u] == MIN_INF or dist[v] > dist[u] + w){
                dist[v] = MIN_INF;
            }
        }
    }
 
}
