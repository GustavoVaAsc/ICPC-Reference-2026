class CHT{
    private:
        vector<pt> hull;
        vector<pt> normal;
 
    ll dot(pt a, pt b) {
        return (conj(a) * b).X;
    }
 
    ll cross(pt a, pt b) {
        return (conj(a) * b).Y;
    }
 
 
    public:
    
        CHT(){
            hull=vector<pt> ();
            normal=vector<pt> ();
        }
 
       
 
    void addLine(pt line) {
       
        while(!normal.empty() && dot(normal.back(), line - hull.back()) > 0) {
            hull.pop_back();
            normal.pop_back();
        }
        if(!hull.empty()) {
            normal.push_back(pt({0,1}) * (line - hull.back()));
        }
        hull.push_back(line);
    }
 
    ll getMinimum(ll x) {
        pt query = {x, 1};
        auto it = lower_bound(normal.begin(), normal.end(), query, [this](pt a, pt b) {
            return cross(a, b) > 0;
        });
        return dot(query, hull[it - normal.begin()]);
    }
 
};
 
 
//ascii https://elcodigoascii.com.ar/
 
inline void solve()
{
    int n,k; cin>>n>>k;
    
    vector<ll> dp(MAX, INF);
    dp[0] = 0;
 
    vector<ll> arr(n+1), pref(n+1);
    pref[0]=0;
    FO(i,n){
        cin>>arr[i+1];
        pref[i+1]=arr[i+1]+pref[i];
    }
    
    CHT qry[MAX];
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=min(k,i);j++)
        {
            if(j>i) continue;
            if(j==1){
                dp[j]=pref[i]*pref[i];
            }
            else{
                dp[j]=pref[i]*pref[i]+qry[j-1].getMinimum(pref[i]);
            }
            qry[j].addLine({-2*pref[i],dp[j]+pref[i]*pref[i]});
        }
    }
    cout<<dp[k]<<endl;
}