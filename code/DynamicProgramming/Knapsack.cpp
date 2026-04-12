void solve(){
    int n,x; cin>>n>>x;
    vector<int> prices(n+1);
    vector<int> pages(n+1);
    for(int i=1; i<=n; i++){cin>>prices[i];}
    for(int i=1; i<=n; i++){cin>>pages[i];}
 
    vector<int> dp(x+1); // dp[prices[i]] -> Max pages I can buy with price i
 
    dp[0] = 0;
    for(int i=1; i<=n; i++){
        for(int j = x; j>=prices[i]; j--){
            dp[j] = max(dp[j],dp[j-prices[i]]+pages[i]);
        }
    }
 
    //for(int i=1; i<=x; i++) cout<<dp[i]<<" ";
    //cout<<endl;
 
    cout<<dp[x]<<endl;
}
