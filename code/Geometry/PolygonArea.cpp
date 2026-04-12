struct point{
    ll x,y;
};

ll CrossP(point a,point b){
    return a.x*b.y-a.y*b.x;
}

inline void solve()
{
    int n; cin>>n;
    ll res=0;
    point p1,p2,p3;
    cin>>p3.x>>p3.y;
    p1.x=p3.x;
    p1.y=p3.y;
    FO(i,n-1)
    {
        cin>>p2.x>>p2.y;
        res+=CrossP(p1,p2);
        p1.x=p2.x;
        p1.y=p2.y;
    }
    res+=CrossP(p1,p3);
    cout<<abs(res)<<endl;
}