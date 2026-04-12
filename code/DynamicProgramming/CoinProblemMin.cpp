void solve(){
    int n, x; cin>>n>>x;
    vector<ll> coins(n);
    for(int i=0; i<n; i++){
        cin>>coins[i];
    }
    
    vector<ll> dp(x+1,0);
    dp[0] = 1;
    for(int i=0; i<=x; i++){
        for(int j=0; j<n; j++){
            if(i-coins[j]>=0){
                dp[i] = (dp[i] + dp[i-coins[j]]);
                dp[i]%=MOD;
            }
        }
    }
        
        
    cout<<dp[x]<<endl;
}
