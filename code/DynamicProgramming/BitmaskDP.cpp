const int limit=20;
vector<pair<ll,ll>> dp((1<<limit));
//ascii https://elcodigoascii.com.ar/

inline void solve()
{
    int n; cin>>n;
    ll x; cin>>x;
    vector<ll> weight(n);
    dp[0]={1,0};
    FO(i,n) cin>>weight[i];
    for(ll i=1;i<(1<<n);i++)
    {
        dp[i]={n+1,0};
        for(int j=0;j<n;j++)
        {
            if(i&(1<<j))
            {
                pair<ll,ll> aux=dp[i^(1<<j)];
                if(aux.second+weight[j]<=x){
                    aux.second+=weight[j];
                }
                else{
                    aux.first++;
                    aux.second=weight[j];
                }
                dp[i]=min(dp[i],aux);
            }
        }
    }
    cout<<dp[(1<<n)-1].first<<endl;
}