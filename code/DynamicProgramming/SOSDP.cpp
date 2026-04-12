typedef long long ll;
typedef vector<int> vec;
const ll mod=1e9+7;
const int NMAX=2e5+3;
const int XMAX=1e6+1e5;
const int BT=20;
 
//ascii https://elcodigoascii.com.ar/
 
 
inline void solve()
{
    int n; cin>>n;
    vector<int> arr(n);
    vector<ll> r(XMAX),d(XMAX),zero(XMAX);
    vector<vector<int>> res(n,vector<int>(3));
    int maxi=0;
    FO(i,n){
         cin>>arr[i];
         r[arr[i]]++;
         d[arr[i]]++;
         
    }
    for(int i=0;i<BT;i++){
        for(int j=0;j<1<<BT;j++)
        {
            if(j&(1<<i)){
                r[j]+=r[j^(1<<i)];
            }
        }
        for(int j=(1<<BT)-1;j>=0;j--){
            if(j&(1<<i)){
                d[j^(1<<i)]+=d[j];
            }
        }
    }
   
 
    FO(i,n){
        cout<<r[arr[i]]<<" "<<d[arr[i]]<<" "<<n-r[(1<<BT)-1-arr[i]]<<endl;
    }
       
}