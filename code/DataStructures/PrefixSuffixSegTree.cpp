typedef long long ll;
typedef vector<int> vec;
typedef vector<pair<int,int>> vpii;
const ll mod=1e9+7;
const int MAX=1e5+3;
const int limit=2e5+3;
const int TAM=2e5+1;
ll t[4*TAM];
ll prefix[4*TAM],suffix[4*TAM],biggest[4*TAM];
//ascii https://elcodigoascii.com.ar/
ll cero=0;
void build(int root,int l,int r,vector<ll> &arr)
{
    if(l==r)
    {
        t[root]=arr[l];
        suffix[root]=max(t[root],cero);
        prefix[root]=max(t[root],cero);
        biggest[root]=max(t[root],cero);
        return;
    }
    int mid=(l+r)/2;
    build(2*root,l,mid,arr);
    build(2*root+1,mid+1,r,arr);
    t[root]=t[2*root]+t[2*root+1];
    biggest[root]=max(biggest[2*root],
    max(biggest[2*root+1],suffix[2*root]+prefix[2*root+1]));
    prefix[root]=max(prefix[2*root],t[2*root]+prefix[2*root+1]);
    suffix[root]=max(suffix[2*root+1],t[2*root+1]+suffix[2*root]);
    
}

void update(int root,int l,int r,int pos,ll val)
{
    if(l==r)
    {
        t[root]=val;
        suffix[root]=max(cero,t[root]);
        prefix[root]=max(cero,t[root]);
        biggest[root]=max(t[root],cero);
        return;
    }
    int mid=(l+r)/2;
    if(pos>mid)
    {
        update(2*root+1,mid+1,r,pos,val);
    }
    else{
        update(2*root,l,mid,pos,val);
    }
    t[root]=t[2*root]+t[2*root+1];
    biggest[root]=max(biggest[2*root],
    max(biggest[2*root+1],suffix[2*root]+prefix[2*root+1]));
    prefix[root]=max(prefix[2*root],t[2*root]+prefix[2*root+1]);
    suffix[root]=max(suffix[2*root+1],t[2*root+1]+suffix[2*root]);
}

ll consult(int root,int l,int r, int a,int b)
{
    if(a>b) return 0;
    if(l==a && r==b) return t[root];
    int mid=(l+r)/2;
    return consult(2*root,l,mid,a,min(b,mid))+
    consult(2*root+1,mid+1,r,max(mid+1,a),b);
}