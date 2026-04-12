struct Edge {
    int u, v;
    ll w;
};
 
void bellmanFord(int V, int E, vector<Edge>& edges, int start) {
    vector<ll> dist(V, INF);
    dist[start] = 0;
    vector<int> prev(V, -1);
 
    int x;
    for (int i = 0; i < V; i++){
        x = -1;
        for (int j = 0; j < E; j++){
            int u = edges[j].u;
            int v = edges[j].v;
            ll weight = edges[j].w;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = max(-INF, (ll) dist[u] + weight);
                prev[v] = u;
                x = v;
            }
        }
    }
 
    if(x == -1){
        cout<<"NO"<<endl; // No negative Cycle
    }else{
        cout<<"YES"<<endl;
        int curr = x;
        for (int i = 0; i < V; ++i)
            curr = prev[curr];
        
        vector<int> cycle;
        for (int x = curr;; x = prev[x]) {
			cycle.push_back(x);
			if (x == curr and cycle.size() > 1) break;
		}
 
        
        reverse(cycle.begin(), cycle.end());
 
        for(int v : cycle)
            cout<<v+1<<" ";
        //cout<<cycle[0]+1<<endl;
    }
 
    
}
 
 
void solve(){
    int n,m; cin>>n>>m;
    vector<Edge> edges;
    for(int i=0; i<m; i++){
        int u,v; ll w; cin>>u>>v>>w;
        edges.push_back({u-1,v-1,w});
    }
    
 
    int dummyNode = n;
    for (int i = 0; i < n; ++i) {
        edges.push_back({dummyNode, i, 0LL});
    }
 
    bellmanFord(n + 1, m + n, edges, dummyNode);
    
}