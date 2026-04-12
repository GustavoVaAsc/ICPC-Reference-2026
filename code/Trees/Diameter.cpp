const int MAX = 2e5+3;
 
#define INF LLONG_MAX 
 
vector<vector<int>> adj(MAX);
bool vis[MAX];
vector<int> dist(MAX);
 
int far;
void dfs(int s, int &max_count, int c){
    vis[s] = true;
    c++;
    for(auto u : adj[s]){
        if(!vis[u]){
            if(c >= max_count){
                max_count = c;
                far = u;
            }
            dfs(u,max_count, c);
        }  
    }
}
 
void resetVisited(int n){
    for(int i=1; i<=n; i++)
        vis[i] = false;
}

void solve(){
    int n; cin>>n;
    for(int i=1; i<=n-1; i++){
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    int max_count = INT_MIN;
    dfs(1,max_count,0);
    resetVisited(n);
    dfs(far,max_count,0);
    if(max_count == INT_MIN){
        cout<<0<<endl;
        return;
    }
 
    cout<<max_count<<endl;
}