void update(int pos,ll u)
{
    pos+=TOP;
    t[pos]=min(u,t[pos]);
    for(int i=pos/2;i;i/=2){
        t[i]=min(t[2*i],t[2*i+1]);
    }
 
}
 
ll query(int a,int b){
    ll res=INF;
    for(a+=TOP,b+=TOP;a<=b;a/=2,b/=2){
        if(a&1){
            res=min(res,t[a++]);
        }
        if(!(b&1)){
            res=min(res,t[b--]);
        }
    }
    return res;
}
 
ll nearest(vector<pt> &reserved,vector<pt> &freecamp,vector<ll> &dist)
{
    vector<tuple<ll,int,ll,int>> events;
    for(int i=0;i<reserved.size();i++){
        pt e=reserved[i];
        events.push_back({e.first,1,e.second,i});
    }
    for(int i=0;i<freecamp.size();i++){
        pt e=freecamp[i];
        events.push_back({e.first,0,e.second,i});
    }
    sort(all(events));
    reverse(all(events));
    fill(t,t+2*MAX,INF);
    ll res=INF;
    for(auto [x,cs,y,id]:events){
        //cout<<x<<" "<<cs<<" "<<y<<endl;
        if(cs==1){
            update(y,x+y);
        }
        else{
            // res=min(res,query(y,TOP-1)-(x+y));
            dist[id]=min(dist[id],query(y,TOP-1)-(x+y));
            //cout<<res<<endl;
        }
    }
    if(res>TOP) return 0;
    //cout<<res<<endl;
    return res;
}

vector<ll> dist(m,INF);
for(int i=0;i<(1<<2);i++)
{
    vector<pt> rot_reserved(n),rot_freecamp(m);
    rot_reserved=reserved;
    rot_freecamp=freecamp;
    FO(j,n){
        if(i&1){
            rot_reserved[j].first=TOP-reserved[j].first;
        }
        if(i&2){
            rot_reserved[j].second=TOP-reserved[j].second;
        }
    }
    FO(j,m){
        if(i&1){
            rot_freecamp[j].first=TOP-freecamp[j].first;
        }
        if(i&2){
            rot_freecamp[j].second=TOP-freecamp[j].second;
        }
    }
    nearest(rot_reserved,rot_freecamp,dist);
}