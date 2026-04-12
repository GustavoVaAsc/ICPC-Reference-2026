const int MAX = 2e6+1;
const int MOD = 1e9+7;
 
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
    vector<vector<int>> arns = {{1,0},{0,1}};
    while(n>0){
        if(n&1) arns = mat_mult(arns,A,2,2,2);
        A = mat_mult(A,A,2,2,2);
        n>>=1;
    }
    return arns;
}
 
void solve(){
    int n; cin>>n;
    vector<vector<int>> a = {{1,1},{1,0}};
    vector<vector<int>> arns = mat_pow(a,n);
 
    cout<<arns[0][1]<<endl;
}
