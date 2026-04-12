const int MAX = 2e5+1;
const int MOD = 1e9+7;
int binpow(int a, int b, int m){
    int arns = 1;
    a%=m;
    while(b>0){
        if(b&1) arns = (arns*a)%m;
        a = (a*a)%m;
        b>>=1; 
    }
    return arns%m;
}
