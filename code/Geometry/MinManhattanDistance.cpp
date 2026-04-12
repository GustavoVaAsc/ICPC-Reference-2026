pt rot(pt a)
{
    return {a.x+a.y,a.y-a.x};
}
 
ll max_coord(ll a,set<ll>& v)
{
    ll min_val=*v.begin();
    ll max_val=*std::prev(v.end());
    return max(abs(a-min_val),abs(a-max_val));
}
 
 
 
inline void solve()
{
    int n; cin>>n;
    vector<pt> points(n);
    set<ll> x_;
    set<ll> y_;
    ll res=0;
    cout<<res<<endl;
    ll a,b; cin>>a>>b;
    pt aux=rot({a,b});
    x_.insert(aux.x);
    y_.insert(aux.y);
    FO(i,n-1){
        cin>>a>>b;
        aux=rot({a,b});
        res=max({res,max_coord(aux.x,x_),max_coord(aux.y,y_)});
        cout<<res<<endl;
        x_.insert(aux.x);
        y_.insert(aux.y);
 
    }
}