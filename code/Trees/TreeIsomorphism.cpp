ll shift(ll x) {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
 
void sztree(int s,vector<vector<int>> &adj,vector<int> &sz,int par=-1)
{
    sz[s]=1;
    for(int ch:adj[s])
    {
        if(ch==par) continue;
        sztree(ch,adj,sz,s);
        sz[s]+=sz[ch];
    }
}
 
int getRoot(int s,vector<vector<int>> &adj,vector<int> &sz,int n,int par=-1){
    for(int ch:adj[s]){
        if(ch==par) continue;
        if(sz[ch]>n/2){
            return getRoot(ch,adj,sz,n,s);
        }
    }
    return s;
}
 
ll treeHash(int s,vector<vector<int>> &adj,int par=-1){
    ll h=1;
    for(int ch:adj[s]){
        if(ch==par) continue;
        h+=shift(treeHash(ch,adj,s));
    }
    return h;
}
 
pair<ll,ll> rootHash(int n)
{
    vector<vector<int>> adj(n+1);
    vector<int> sz(n+1);
    FO(i,n-1){
        int a,b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    sztree(1,adj,sz);
    pair<ll,ll> candidates;
    int centroid1=getRoot(1,adj,sz,n);
    sztree(centroid1,adj,sz);
    int centroid2=-1;
    for(int ch:adj[centroid1]){
        if(n-sz[ch]<=n/2){
            centroid2=ch;
            break;
        }
    }
    candidates.first=treeHash(centroid1,adj);
    if(centroid2!=-1){
        candidates.second=treeHash(centroid2,adj);
    }
    else{
        candidates.second=-1;
    }
    return candidates;
}