const int MAX = 2e6+1;
const int MOD = 1e9+7;
const int INF = 4e18;
 
int modInv(int num){
    if(num == 1) return 1;
    return (MOD - ((MOD/num)*modInv(MOD%num))%MOD+MOD)%MOD;
}
 
vector<vector<int>> mat_zum(vector<vector<int>> &A, vector<vector<int>> &B, int n, int m, int p){
    vector<vector<int>> arns(n,vector<int> (p, INF));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            for(int k=0; k<p; k++){ 
                if (A[i][j] < INF && B[j][k] < INF) {
                    arns[i][k] = min(arns[i][k], A[i][j] + B[j][k]);
                }
            }   
        }
    }
 
    return arns;
}
 
vector<vector<int>> mat_pow(vector<vector<int>> &A, int n){
    int sz = A.size();
    vector<vector<int>> arns(sz,vector<int> (sz,INF));
    for(int i = 0; i < sz; i++) arns[i][i] = 0;
    while(n>0){
        if(n&1) arns = mat_zum(arns,A,sz,sz,sz);
        A = mat_zum(A,A,sz,sz,sz);
        n>>=1;
    }
    return arns;
}
 
void solve(){
    int n, m, k; cin>>n>>m>>k;
    vector<vector<int>> adj(n,vector<int>(n,INF));
    for(int i=0; i<m; i++){
        int a,b,c; cin>>a>>b>>c;
        a--; b--;
        adj[a][b]=min(adj[a][b], c);
    }
    vector<vector<int>> arns = mat_pow(adj,k);
    if(arns[0][n-1] == INF) cout<<"-1"<<endl;
    else cout<<arns[0][n-1]<<endl;
}
