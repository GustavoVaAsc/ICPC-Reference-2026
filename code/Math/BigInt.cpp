static const __int128 MOD = (__int128)1000000000000000031ULL;
static const __int128 g   = (__int128)42ULL;              
 
ostream &operator<<(ostream &os, const __int128 & value){
    char buffer[64];
    char *pos = end(buffer)-1;
    *pos = '\0';
    __int128 tmp = value < 0 ? -value : value;
 
    do{
        --pos;
        *pos = tmp%10 + '0';
        tmp/=10;
    }while(tmp!=0);
    if(value < 0){
        --pos;
        *pos = '-';
    }
 
    return os << pos;
}
 
inline __int128 mulm(__int128 a, __int128 b){
    __uint128_t z = ( (__uint128_t)a * (__uint128_t)b );
    return (__int128)( z % MOD );
}
__int128 binpow(__int128 a, __int128 e){
    __int128 r = 1;
    while (e > 0){
        if (e & 1) r = mulm(r, a);
        a = mulm(a, a);
        e >>= 1;
    }
    return r;
}
 
void solve(){
	int n; cin>>n;
 
    __int128 p = 300;
	__int128 cnt = 1;
	for(ll i = 1000000LL;i>n;i--){
		p = binpow(g,p);
	}
	cout << p << '\n';
}