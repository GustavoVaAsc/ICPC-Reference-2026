// Breadth First Search
vector<int> adj[MAXN];
int dist[MAXN];

void bfs(int start) {
    queue<int> q;
    memset(dist, -1, sizeof(dist));
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}
