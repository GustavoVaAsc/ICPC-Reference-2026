#define ll long long
#define all(x) x.begin(), x.end()
 
mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
const int MOD = 1e9 + 9;
const ll BASE = uniform_int_distribution<ll>(0, MOD-1)(rng);
 
vector<ll> pows = {1};
vector<ll> p_hash;
 
void hash_str(const string &s){
    p_hash.assign(s.size()+1, 0);
 
    while(pows.size() <= s.size()){
	pows.push_back((pows.back()* BASE)%MOD);
    }
 
    p_hash[0] = 0;
    for(int i=0; i<s.size(); i++){
	p_hash[i+1] = ((p_hash[i]* BASE)% MOD + s[i])%MOD;
    }
}
 
ll get_hash(int l, int r){
    ll raw = (p_hash[r+1] - (p_hash[l] * pows[r-l+1]));
    return (raw % MOD  + MOD) % MOD;
}
 
inline void solve(){
    string s; cin>>s;
    int n = s.size();
 
    hash_str(s);
 
    for(int i=0; i<n-1; i++){
	if(get_hash(0,i) == get_hash(n-i-1, n-1)){
	    cout<<i+1<<" ";
	}
    }
    cout<<endl;
}
