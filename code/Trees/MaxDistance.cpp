#define INF LLONG_MAX 
 
vector<vector<int>> adj(MAX);
vector<int> f(MAX,0); // f(x) = maximum distance from node x to any node of its subtree
vector<int> g(MAX,0); // g(x) = maximum distance from any node to x  outside its subtree
vector<int> arns(MAX,0); // arns(x) = max(f(x),g(x))
 
 
void dfsA(int s, int e){
    for(auto u : adj[s]){
        if(u == e) continue;
        dfsA(u,s);
        if(f[u]+1 > f[s]){ // Maximum distance + 1 of u > Max dist of predecessor
            g[s] = f[s];   // Maximum distance from any node outside of s subtree is f[s] 
            f[s] = f[u] + 1;
        }else if(f[u]+1>g[s]){
            g[s] = f[u]+1; // Maximum distance from any node outside of s subtree is f[u]+1
        }
    }
}
 
void dfsB(int s, int e, int to){
    arns[s] = max(to, f[s]);
    for(auto u : adj[s]){
        if(u == e) continue;
        if(f[u]+1 == f[s]) dfsB(u,s, max(to,g[s])+1);
        else dfsB(u,s, arns[s]+1);
    }
}
 
void solve(){
    int n; cin>>n;
    for(int i=1; i<=n-1; i++){
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    dfsA(1,0);
    dfsB(1,0,0);
 
    for(int i=1;i<=n; i++)
        cout<<arns[i]<<" ";
    cout<<endl;
}
