const int m=30;
int succesorM[limit][m];
//ascii https://elcodigoascii.com.ar/

inline void solve()
{
    int n,q; cin>>n>>q;
    int res,aux;
    ll k;
    lFOR(i,n){
        cin>>succesorM[i][0];
    }
    FOR(j,1,m)
    {
        lFOR(i,n)
        {
            succesorM[i][j]=succesorM[succesorM[i][j-1]][j-1];
        }
    }
    FO(i,q)
    {
        cin>>res>>k;
        aux=0;
        while(k)
        {
            if(k%2){
                res=succesorM[res][aux];
            }
            k/=2;
            aux++;
        }
        cout<<res<<endl;
    }
}