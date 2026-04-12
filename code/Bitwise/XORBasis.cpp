const int D = 32;
ll basis[D];
ll bs_len = 0;
 
void add(int x){
    for(int i=0; i<D; i++){
	if((x & 1 << i) == 0) continue;
 
	if(!basis[i]){
	    basis[i] = x;
	    bs_len++;
	    return;
	}
 
	x ^= basis[i];
    }
}
 
void add2(ll x){
    for(int i=D-1; i>=0; i--){
	if((x>>i) & 1){
	    if(!basis[i]){
		basis[i] = x;
		return;
	    }
	    x^=basis[i];
	}
    }
}
 
inline void solve(){
    int n; cin>>n;
    vector<int> st(n);
    for(int &x : st) cin>>x;
    
    for(int vec : st){
	add2(vec);
    }
 
    ll max_xor = 0;
 
    for(int i=D-1; i>=0; i--){
	max_xor = max(max_xor, max_xor^basis[i]);
    }
 
    cout<<max_xor<<endl;
}
const int D = 32;
ll basis[D];
ll bs_len = 0;
 
void add(int x){
    for(int i=0; i<D; i++){
	if((x & 1 << i) == 0) continue;
 
	if(!basis[i]){
	    basis[i] = x;
	    bs_len++;
	    return;
	}
 
	x ^= basis[i];
    }
}
 
void add2(ll x){
    for(int i=D-1; i>=0; i--){
	if((x>>i) & 1){
	    if(!basis[i]){
		basis[i] = x;
		return;
	    }
	    x^=basis[i];
	}
    }
}
 
inline void solve(){
    int n; cin>>n;
    vector<int> st(n);
    for(int &x : st) cin>>x;
    
    for(int vec : st){
	add2(vec);
    }
 
    ll max_xor = 0;
 
    for(int i=D-1; i>=0; i--){
	max_xor = max(max_xor, max_xor^basis[i]);
    }
 
    cout<<max_xor<<endl;
}
