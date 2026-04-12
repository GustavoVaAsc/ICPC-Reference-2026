vector<ll> fact(MAX);
vector<ll> i_fact(MAX);
 
ll binpow(ll a, ll b){
    ll arns = 1;
    a%=MOD;
    while(b>0){
        if(b&1)
           arns = (arns*a)%MOD;
        a = (a*a)%MOD;
        b>>=1; 
    }
    return arns;
}
 
ll modInv(ll a, ll m=MOD){
    return binpow(a,MOD-2);
}
 
void factorial(){
    fact[0] = fact[1] = 1;
    for(int i=2; i<MAX; i++){
        fact[i] = (fact[i-1] * i)%MOD;
    }
 
    i_fact[MAX-1] = modInv(fact[MAX-1]);
    for(int i=MAX-2; i>=0; i--){
        i_fact[i] = (i_fact[i+1]*(i+1))%MOD;
    }
 
}
 
ll bn_coef(ll n, ll k){
    return fact[n] * i_fact[n-k]%MOD *i_fact[k]%MOD;
}
