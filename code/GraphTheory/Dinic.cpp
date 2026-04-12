const int MAX = 503;
 
#define INF LLONG_MAX 
#define pii pair<int,int>
#define fi first
#define sc second
#define all(x) x.begin(),x.end()
 
struct FlowEdge{
    int u,v;
    ll flow=0, cap;
    FlowEdge(int u, int v, ll cap) : u(u), v(v), cap(cap){};
};
 
struct Dinic{
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, s, t; // Vertices, Source, Sink
    int id = 0;
    vector<int> level, next;
    queue<int> q;
 
    Dinic(int n, int s, int t) : n(n), s(s), t(t){
        adj.resize(n);
        level.resize(n);
        next.resize(n);
        fill(all(level), -1);
        level[s] = 0;
        q.push(s);
    }
 
    
    void addEdge(int u, int v, ll cap){
        edges.emplace_back(u,v,cap);
        edges.emplace_back(v,u,0);
        adj[u].push_back(id++);
        adj[v].push_back(id++);
    }
 
    bool bfs(){
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(auto e : adj[u]){
                // Saturated
                if(edges[e].cap - edges[e].flow < 1) continue;
                // Visited
                if(level[edges[e].v] != -1) continue;
 
                level[edges[e].v] = level[edges[e].u] +1;
                q.push(edges[e].v);
            }
        }
 
        return level[t] != -1;
    }
 
    ll dfs(int u, ll flow){
        if(flow == 0) return 0;
        if(u == t) return flow;
        // cid is current id
        for(int &cid = next[u]; cid<adj[u].size(); cid++){
            int e = adj[u][cid];
            int v = edges[e].v;
 
            if(level[edges[e].u] + 1 != level[v] or edges[e].cap - edges[e].flow < 1)
                continue;
            ll f = dfs(v, min(flow, edges[e].cap - edges[e].flow));
            if(f == 0) continue;
 
            edges[e].flow += f;
            edges[e^1].flow -= f;
            return f;
        }
        return 0;
    }
 
    ll maxFlow(){
        ll flow = 0;
        while(bfs()){ // While there are aug paths
            fill(all(next), 0);
            for(ll f = dfs(s, INF); f!=0ll; f = dfs(s,INF)) flow+=f;
            fill(all(level), -1);
            level[s] = 0;
            q.push(s);
        }
 
        return flow;
    }
 
    vector<pii> minCut(){
        vector<pii> arns;
        fill(all(level), -1);
        level[s] = 0;
        q.push(s);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int id = 0; id<adj[u].size(); id++){
                int e = adj[u][id];
                if(level[edges[e].v] == -1 and edges[e].cap - edges[e].flow > 0){
                    q.push(edges[e].v);
                    level[edges[e].v] = level[edges[e].u] + 1;
                }
            }
        }
 
        for(int i=0; i<level.size(); i++){
            if(level[i] != -1){
                for(int id=0; id<adj[i].size(); id++){
                    int e = adj[i][id];
                    if(level[edges[e].v] == -1 and edges[e].cap - edges[e].flow == 0)
                        arns.emplace_back(edges[e].u, edges[e].v);
                }
            }
        }
 
        return arns;
    }
 
    vector<pii> maxMatching(){
        vector<pii> arns;
        fill(all(level), -1); // Reset levels.
        level[s] = 0;
        q.push(s);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int id = 0; id < adj[u].size(); id++){
                int e = adj[u][id];
                if(level[edges[e].v] == -1 and edges[e].cap - edges[e].flow == 0 and edges[e].flow != 0ll){
                    q.push(edges[e].v);
                    level[edges[e].v] = level[edges[e].u] +1;
                }
            }
        }
 
        for(int i=0; i<level.size(); i++){
            if(level[i] != -1){
                for(int id=0; id<adj[i].size(); id++){
                    int e = adj[i][id];
                    if(edges[e].u != s and edges[e].v != t and edges[e].cap - edges[e].flow == 0 and edges[e].flow != 0ll)
                            arns.emplace_back(edges[e].u, edges[e].v);
                }
            }
        }
        return arns;
    }
 
};
