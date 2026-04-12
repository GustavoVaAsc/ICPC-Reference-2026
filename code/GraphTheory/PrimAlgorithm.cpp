const int MAX = 2e5+3;
 
#define INF LLONG_MAX 
typedef pair<ll, ll> pll;
 
ll prim(int V, int E, vector<vector<pll>> &adj) {
  
    priority_queue<pll, vector<pll>, greater<pll>> pq; 
    
    vector<bool> visited(V, false);
    
    ll res = 0;
    
    pq.push({0, 0});
    
    while(!pq.empty()){
        auto p = pq.top();
        pq.pop();
        
        int wt = p.first; 
        int u = p.second;
        
        if(visited[u] == true){
            continue; 
        }
        
        res += wt;
        visited[u] = true;
        
        for(auto v : adj[u]){
            if(visited[v.first] == false){
                pq.push({v.second, v.first});
            }
        }
    }
 
    for(int i=0; i<V; i++){
        if(!visited[i])
            return -1;
    }
    
    return res;
}