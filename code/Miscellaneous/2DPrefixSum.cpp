void solve(){
    int n,q; cin>>n>>q;
    char forest[n+1][n+1];
 
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin>>forest[i][j];
        }
    }
    
    vector<vector<int>> dp(n+1, vector<int> (n+1,0));
    
 
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            dp[i][j] =  dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1];
            if(forest[i][j] == '*') dp[i][j]++;
        }
    }
 
    
 
    for(int i=0; i<q; i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        cout<<dp[c][d] - dp[a-1][d] - dp[c][b-1] + dp[a-1][b-1]<<endl;
    }
    
}
