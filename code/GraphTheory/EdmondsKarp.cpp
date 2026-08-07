vector<vector<int>> adj(MAX);
vector<vector<int>> cap(MAX, vector<int>(MAX));
 
int bfs(int s, int t, vector<int> &parent){
    parent[s] = -2;
    queue<pii> q;
    q.push({s,INF});
 
    while(!q.empty()){
        int u = q.front().fi;
        int flow = q.front().sc;
        q.pop();
 
        for(int v : adj[u]){
            if(parent[v] == -1 and cap[u][v]){
                parent[v] = u;
                int new_flow = min(flow, cap[u][v]);
                if(v == t) return new_flow;
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}
 
int edmond_karp(int s, int t, int n){
    vector<int> parent(n+1,-1);
    int flow = 0;
    int new_flow;
    while(new_flow = bfs(s,t,parent)){
        flow += new_flow;
        int cur = t;
        while(cur != s){
            int prev = parent[cur];
            cap[prev][cur] -=  new_flow;
            cap[cur][prev] += new_flow;
            cur = prev;
        }
        fill(parent.begin(), parent.end(), -1);
    }
 
    return flow;
}
