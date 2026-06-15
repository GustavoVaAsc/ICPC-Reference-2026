typedef long long ll;

struct llm {
    static const ll MOD=1e9+7;
    ll v;
    llm& operator+=(const llm& o){v=(v+o.v)%MOD;return *this;}
    llm& operator-=(const llm& o){v=(v-o.v+MOD)%MOD;return *this;}
    llm& operator*=(const llm& o){v=v*o.v%MOD;return *this;}
    static ll pw(ll x,ll k){ll r=1;while(k){if(k&1)r=r*x%MOD;x=x*x%MOD;k/=2;}return r;}
    llm& operator/=(const llm& o){v=v*pw(o.v,MOD-2)%MOD;return *this;}
    friend llm operator+(llm l,const llm r){return l+=r;}
    friend llm operator-(llm l,const llm r){return l-=r;}
    friend llm operator*(llm l,const llm r){return l*=r;}
    friend llm operator/(llm l,const llm r){return l/=r;}

};