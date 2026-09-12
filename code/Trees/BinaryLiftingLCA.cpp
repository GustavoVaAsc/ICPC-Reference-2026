void dfs(int s,vector<vector<pair<int,int>>> &adj,int par=-1, int weight=0)
{
    tin[s]=++tim;
    wlca[s][0]=weight;
    //cout<<weight<<endl;
    lca[s][0]=par;
    for(auto [ch,w]:adj[s]){
        if(ch!=par){
            dfs(ch,adj,s,w);
        }
    }
    tout[s]=++tim;
}
 
bool ancestor(int a,int b){
    if(a==-1) return true;
    if(b==-1) return false;
    return tin[a]<=tin[b] && tout[b]<=tout[a];
}
 
int getLca(int a,int b)
{
    if(ancestor(a,b)) return a;
    if(ancestor(b,a)) return b;
    for(int i=MDEPTH-1;i>=0;i--)
    {
        //cout<<lca[a][i]<<endl;
        if(!ancestor(lca[a][i],b)){
            a=lca[a][i];
        }
    }
    
    return lca[a][0];
}