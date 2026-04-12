typedef long long ll;
typedef vector<int> vec;
typedef vector<pair<int,int>> vpii;
const ll mod=1e9+7;
const int MAX=1e5+3;
const int limit=2e5+3;
const int TAM=2e5+1;
ll t[4*TAM];
ll op[4*TAM];
int type[4*TAM];
//ascii https://elcodigoascii.com.ar/

void propagate(int root,int l,int r)
{
    if(type[root]==1)
    {
        t[root]+=op[root]*(r+1-l);
        if(l!=r){
            op[2*root]+=op[root];
            op[2*root+1]+=op[root];
            type[2*root+1]=max(1,type[2*root+1]);
            type[2*root]=max(1,type[2*root]);
        }
    }
    else
    {
        if(type[root]==2){
            t[root]=op[root]*(r+1-l);
            if(l!=r){
                op[2*root]=op[root];
                op[2*root+1]=op[root];
                type[2*root+1]=2;
                type[2*root]=2;
            }
        }
    }
    op[root]=0;
    type[root]=0;
}

void build(int root,int l,int r,vector<ll> &arr)
{
    if(l==r)
    {
        t[root]=arr[l];
        op[root]=0;
        type[root]=0;
        return;
    }
    int mid=(l+r)/2;
    build(2*root,l,mid,arr);
    build(2*root+1,mid+1,r,arr);
    t[root]=t[2*root]+t[2*root+1];
    op[root]=0;
    type[root]=0;
}

void sum(int root,int l,int r,int a,int b,ll val)
{
    propagate(root,l,r);
    if(a>b) return;
    if(l==a && r==b)
    {
        op[root]=val;
        type[root]=1;
        propagate(root,l,r);
        return;
    } 
    int mid=(l+r)/2;
    sum(2*root,l,mid,a,min(b,mid),val);
    sum(2*root+1,mid+1,r,max(mid+1,a),b,val);
    t[root]=t[2*root]+t[2*root+1];
}

void setR(int root,int l,int r,int a,int b,ll val)
{
    propagate(root,l,r);
    if(a>b) return;
    if(l==a && r==b)
    {
        op[root]=val;
        type[root]=2;
        propagate(root,l,r);
        return;
    } 
    int mid=(l+r)/2;
    setR(2*root,l,mid,a,min(b,mid),val);
    setR(2*root+1,mid+1,r,max(mid+1,a),b,val);
    t[root]=t[2*root]+t[2*root+1];
}

ll consult(int root,int l,int r, int a,int b)
{
    propagate(root,l,r);
    if(a>b) return 0;
    if(l==a && r==b){
        return t[root];
    } 
    int mid=(l+r)/2;
    return consult(2*root,l,mid,a,min(b,mid))+
    consult(2*root+1,mid+1,r,max(mid+1,a),b);
} 