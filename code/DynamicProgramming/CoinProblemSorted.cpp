void solve(){
    int n, x; cin>>n>>x;
    vector<ll> coins(n);
    for(int i=0; i<n; i++){
        cin>>coins[i];
    }
    
    int dp[102][1000005];
    dp[0][0] = 1;
    for(int i=1; i<=n; i++){
        for(int j=0; j<=x; j++){
            dp[i][j] = dp[i-1][j];
            int l = j-coins[i-1];
            if(l>=0){
                dp[i][j] += (dp[i][l])%MOD;
                dp[i][j]%=MOD;
            }
        }
    }
        
        
    cout<<dp[n][x]%MOD<<endl;
}
