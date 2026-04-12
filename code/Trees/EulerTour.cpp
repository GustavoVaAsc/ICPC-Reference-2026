vector<vector<int>> adj(MAX);
vector<int> in(MAX);
vector<int> out(MAX);
vector<ll> values(MAX);
vector<ll> flat(MAX);
int timer = 1;
 
ll t[2*MAX];
 
void build(int n){
    for(int i=1; i<=n; i++)
        t[n+i] = flat[i];
    
    for(int i=n; i>=1; i--)
        t[i] = t[i<<1] + t[i<<1 | 1];
    
}
 
void update(int idx, int v, int n){
    for(t[idx += n] = v; idx > 1; idx >>= 1)
        t[idx >> 1] = t[idx ^ 1] + t[idx];
 
}
 
// Query [l,r)
 
ll query(int l, int r, int n){
    ll arns = 0;
    for(l+=n, r+=n; l<r; l>>=1, r>>=1){
        if (l & 1) arns += t[l++];
        if (r & 1) arns += t[--r];
    }
    return arns;
}
 
void eulerTour(int s, int e){
    in[s] = timer;
    flat[timer++] = values[s];
    for(auto u : adj[s]){
        if (u == e) continue;
        eulerTour(u,s);
    }
    out[s] = timer;
}
 
void solve(){
    int n,q; cin>>n>>q;
    for(int i=1; i<=n; i++){
        cin>>values[i];
    }
 
    for(int i=1; i<=n-1; i++){
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    eulerTour(1,0);
    /*
    for(int i=1; i<=n; i++){
        cout<<in[i]<<endl;
    }
 
    for(int i=1; i<=n; i++){
        cout<<out[i]<<endl;
    }
        */
    
    build(n);
 
    for(int i=1; i<=q; i++){
        int a; cin>>a;
        if(a == 1){
            int v; int x; cin>>v>>x;
            update(in[v],x,n);
        }else{
            int v; cin>>v;
            cout<<query(in[v],out[v],n)<<endl;
        }
    }
}
