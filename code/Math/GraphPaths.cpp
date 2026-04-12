vector<vector<int>> mat_mult(vector<vector<int>> &A, vector<vector<int>> &B, int n, int m, int p){
    vector<vector<int>> arns(n,vector<int> (p));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            for(int k=0; k<p; k++){ 
                arns[i][k] += A[i][j] * B[j][k];
                arns[i][k]%=MOD;
            }   
        }
    }
 
    return arns;
}
 
vector<vector<int>> mat_pow(vector<vector<int>> &A, int n){
    int sz = A.size();
    vector<vector<int>> arns(sz,vector<int> (sz,0));
    for(int i=0; i<sz; i++)
        arns[i][i] = 1;
    while(n>0){
        if(n&1) arns = mat_mult(arns,A,sz,sz,sz);
        A = mat_mult(A,A,sz,sz,sz);
        n>>=1;
    }
    return arns;
}
 
void solve(){
    int n, m, k; cin>>n>>m>>k;
    vector<vector<int>> adj(n,vector<int>(n,0));
    for(int i=0; i<m; i++){
        int a,b; cin>>a>>b;
        a--; b--;
        adj[a][b]++;
    }
    vector<vector<int>> arns = mat_pow(adj,k);
    cout<<arns[0][n-1]<<endl;
}
