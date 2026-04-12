// Kosaraju Algorithm
struct TwoSAT{
    int vars;
    int n;
    vector<vector<int>> adj, adj_t;
    vector<bool> used;
    vector<int> order, comp;
    vector<bool> values; 
 
    TwoSAT(int _vars) : 
        vars(_vars), 
        n(2 * vars), 
        adj(n), 
        adj_t(n), 
        used(n),
        order(),
        comp(n,-1),
        values(n){
            order.reserve(n);
        }
    
    void dfsA(int s){
        used[s] = true;
        for(int u : adj[s]){
            if(!used[u]) dfsA(u);
        }
        order.push_back(s);
    }
 
    void dfsB(int s, int sc){
        comp[s] = sc;
        for(int u : adj_t[s]){
            if(comp[u] == -1) dfsB(u,sc);
        }
    }
 
    bool twoSAT(){
        order.clear();
        used.assign(n, false);
 
        for(int i=0; i<n; i++){
            if(!used[i]) dfsA(i);
        }
 
        comp.assign(n, -1);
 
        for(int i=0, j=0; i<n; i++){
            int v = order[n-i-1];
            if(comp[v] == -1) dfsB(v, j++);
        }
 
        values.assign(vars, false);
 
        for(int i=0; i<n; i+=2){
            if(comp[i] == comp[i+1]) return false;
            values[i/2] = comp[i] > comp[i+1];
        }
        return true;
    }
 
    void add_disjunction(int a, bool na, int b, bool nb){
        a = 2* a ^ na;
        b = 2* b ^ nb;
 
        int not_a = a^1;
        int not_b = b^1;
 
        adj[not_a].push_back(b);
        adj[not_b].push_back(a);
        adj_t[b].push_back(not_a);
        adj_t[a].push_back(not_b);
    }
};
