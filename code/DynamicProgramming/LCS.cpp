vector<int> lcs(vector<int> const& a, vector<int> const &b, int n, int m){
    vector<vector<int>> dp (n+1,vector<int> (m+1,0));
 
    for(int i=1; i<=n; i++){
        for(int j=1;j<=m; j++){
            if(a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1]+1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
 
    int ind = dp[n][m];
    // Note: if we have characters, we must set ind+1 size
    // and set the last character as terminal '\0'
    vector<int> arns(ind); 
    int i = n, j = m;
 
    while(i>0 and j>0){
        if(a[i-1] == b[j-1]){
            arns[ind-1] = a[i-1];
            i--;
            j--;
            ind--;
        }else if(dp[i-1][j] > dp[i][j-1]) i--;
        else j--;
    }
 
    return arns;
}
