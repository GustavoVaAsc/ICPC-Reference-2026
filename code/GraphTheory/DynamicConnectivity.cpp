const int BS=18;
//ascii https://elcodigoascii.com.ar/
 
 
struct query{
    int citya,cityb,l,r,id; 
    query(int citya, int cityb, int l, int r,int id): citya(citya), cityb(cityb), l(l), r(r),
    id(id)
    {}
};
 
class DSU{
    private:
        vector<int> leader;
        vector<int> sz;
        int n;
    
        int getLeader(int a){
            if(leader[a]==a) return a;
            leader[a]=getLeader(leader[a]);
            return leader[a];
        }
 
    public:
        DSU(int n): n(n){
            leader=vector<int> (n+1);
            sz=vector<int> (n+1,1);
            FO(i,n+1){
                leader[i]=i;
            }
        }
 
        void clear(){
            leader=vector<int> (n+1);
            sz=vector<int> (n+1,1);
            FO(i,n+1){
                leader[i]=i;
            }
        }
 
        void unite(int a,int b){
            a=getLeader(a);
            b=getLeader(b);
            if(a==b) return;
            if(sz[a]<sz[b]){
                swap(a,b);
            }
            leader[b]=a;
            sz[a]+=sz[b];
        }
 
        bool isConnected(int a,int b){
            return getLeader(a)==getLeader(b);
        }
        
};
 
 
inline void solve()
{
    int n,m,q; cin>>n>>m>>q;
    vector<vector<query>> timeline(m);
    vector<vector<query>> nxt(m);
    vector<pair<int,int>> edges(m);
    vector<int> res(q,-2);
    DSU dj(n);
    FO(i,m){
        int a,b; cin>>a>>b;
        edges[i]={a,b};
    }
    
    FO(i,q){
        int a,b; cin>>a>>b;
        if(a==b) res[i]=-1;
        else timeline[(m-1)/2].push_back({a,b,0,m-1,i});
    }
    FO(i,BS){
        dj.clear();
        FO(i,m) nxt[i].clear();
        for(int j=0;j<m;j++)
        {
            dj.unite(edges[j].X,edges[j].Y);
        
            for(query &q:timeline[j])
            {
                if(q.l>q.r) continue;
                if(dj.isConnected(q.citya,q.cityb)){
                
                    res[q.id]=j;
                    int mid=(j-1+q.l)/2;
                    nxt[mid].push_back(query(q.citya,q.cityb,q.l,j-1,q.id));
                }
                else{
                    int mid=(j+1+q.r)/2;
                    nxt[mid].push_back(query(q.citya,q.cityb,j+1,q.r,q.id));
                }
            }
        }
        timeline.swap(nxt);
    }
    for(int r:res){
        cout<<r+1<<endl;
    }
}