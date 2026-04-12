const ll mod=1e9+7;
const ll MAX=8e18;
const ll limit=1e9+1;
//ascii https://elcodigoascii.com.ar/

ll distance(point a,point b){
    return (a.X-b.X)*(a.X-b.X)+(a.Y-b.Y)*(a.Y-b.Y);
}

inline void solve()
{
    int n; cin>>n;
    vector<point> sortedX(n);
    set<point> sortedY;
    FO(i,n)
    {
        ll x,y; cin>>x>>y;
        sortedX[i]=make_pair(x,y);
    }
    sort(all(sortedX));
    sortedY.insert(make_pair(sortedX[0].Y,sortedX[0].X));
    ll d,minSquare=MAX;
    int j=0;
    FOR(i,1,n)
    {
        d=ceil(sqrt(minSquare));
        while(sortedX[i].X-sortedX[j].X>d)
        {
            sortedY.erase(make_pair(sortedX[j].Y,sortedX[j].X));
            j++;
        }
        auto lower=sortedY.lower_bound(make_pair(sortedX[i].Y-d,0));
        auto upper=sortedY.upper_bound(make_pair(sortedX[i].Y+d,0));
        for(auto pointer=lower;pointer!=upper;pointer++)
        {
            minSquare=min(minSquare,distance(*pointer,make_pair(sortedX[i].Y,sortedX[i].X)));
        }
        sortedY.insert(make_pair(sortedX[i].Y,sortedX[i].X));
    }
    cout<<minSquare<<endl;
}