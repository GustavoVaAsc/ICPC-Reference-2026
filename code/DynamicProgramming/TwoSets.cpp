void solve(){
    int n; cin>>n;
 
    int tw = n*(n+1)/2;
    if(tw%2 == 1){
        cout<<0<<endl;
        return;
    }
    tw = tw/2;
 
    vector<int> dp(tw+1,0);
 
    dp[0] = 1;
 
    for(int i=1; i<n; i++){
        for(int j=tw; j>=i; j--){
            dp[j] = (dp[j] + dp[j-i])%MOD;
        }
    }
 
    cout<<dp[tw]<<endl;
    
}
