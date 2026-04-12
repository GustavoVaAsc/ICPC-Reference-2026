#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#define pii pair<int,int>
 
using namespace std;
using namespace __gnu_pbds;
 
#define int long long
 
const int MAX = 2e5+1;
const int INF = LLONG_MAX;
 
template<typename T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
void solve(){
    int n,q; cin>>n>>q;
    vector<int> v(n);
    Tree<pii> oset;
 
    for(int &x : v) cin>>x;
 
    for(int i=0; i<n; i++){
        oset.insert({v[i],i});
    }
 
    for(int i=0; i<q;i++){
        char ty; cin>>ty;
        if(ty == '!'){
            int k, s; cin>>k>>s;
            k--;
            oset.erase({v[k],k});
            v[k] = s;
            oset.insert({v[k],k});
        }else{
            int a, b; cin>>a>>b;
            cout<<oset.order_of_key({b,INF}) - oset.order_of_key({a-1,INF})<<endl;
        }
    }
    
}
