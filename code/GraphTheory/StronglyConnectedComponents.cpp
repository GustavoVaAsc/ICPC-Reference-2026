 
const int MAX = 2e5+3;
 
#define INF LLONG_MAX 
typedef pair<ll, ll> pll;
 
vector<vector<int>> adj(MAX);
vector<vector<int>> t_adj(MAX);
vector<int> v_id(MAX);
bool visited[MAX];
vector<int> order; // Append the respective nodes with dfsA order
 
// Calculate vertex order
void dfsA(int s){
    visited[s] = true;
    for(int u : adj[s]){
        if(!visited[u])
            dfsA(u);
    }
    order.push_back(s);
}
 
// Set its component id to every vertex
void dfsB(int s, int c){
    visited[s] = true;
    for(int u: t_adj[s]){
        if(!visited[u])
            dfsB(u,c);
    }
    v_id[s] = c; 
}
 
 
void solve(){
    int n,m; cin>>n>>m;
    
    for(int i=0; i<m; i++){
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        t_adj[v].push_back(u);
    }
 
    for(int i=1; i<=n; i++){
        if(!visited[i])
            dfsA(i);
    }
 
    for(int i=1; i<=n; i++)
        visited[i] = false;
 
    reverse(order.begin(),order.end());
 
    int c = 0;
    for(int i=0; i<order.size(); i++){    
        if(!visited[order[i]]){
            c++;
            dfsB(order[i],c);
        }       
    }
 
    if(c == 1){
        cout<<"YES"<<endl;
    }else{
        bool flag1 = false, flag2 = false;
        cout<<"NO"<<endl;
        int arns[2];
        for(int i=1; i<=n; i++){
            if(v_id[i] == 1 and flag1 == false){
                flag1 = true;
                arns[0] = i;
            }
 
            if(v_id[i] == 2 and flag2 == false){
                flag2 = true;
                arns[1] = i;
            }
 
            if(flag1 == true and flag2 ==true) break;
        }
        cout<<arns[1]<<" "<<arns[0]<<endl;
    }
}