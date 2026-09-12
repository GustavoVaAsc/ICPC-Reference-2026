

int n,m,q; cin>>n>>m>>q;
vector<vector<query>> timeline(m);
vector<vector<query>> nxt(m);

FO(i,q){
    int a,b; cin>>a>>b;
    timeline[(m-1)/2].push_back({query{}});
}
FO(i,BS){

    FO(i,m) nxt[i].clear();
    for(int j=0;j<m;j++)
    {
        
        for(query &q:timeline[j])
        {
            if(q.l>q.r) continue;
            if(possible()){
            
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
