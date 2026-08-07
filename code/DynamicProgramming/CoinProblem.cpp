void solve(){
    int n, x; cin>>n>>x;
    vector<ll> coins(n);
    for(int i=0; i<n; i++){
        cin>>coins[i];
    }
    
    vector<ll> dp(x+1,LLONG_MAX);
    dp[0] = 0;
    for(int i=0; i<=x; i++){
        for(int j=0; j<n; j++){
            if(i-coins[j]>=0){
                dp[i] = min(dp[i], dp[i-coins[j]]+1);
            }
            
        }
    }
    
    if(dp[x] != LLONG_MAX){
        cout<<dp[x]<<endl;
    }else{
        cout<<"-1"<<endl;
    }
        
    
}