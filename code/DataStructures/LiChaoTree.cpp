typedef long long ll;
typedef complex<ll> pt;
typedef vector<int> vec;

const ll mod=1e9+7;
const ll MAX=1e5+3;
const ll INF=1e18;

pt lines[4*MAX];

//Li Chao Tree

ll dot(pt a,pt b){
    return a.X*b.X+a.Y*b.Y;
}

ll f(pt line,ll val){
    return dot(line,pt{val,1});
}

void addLine(pt cur,int root=1,int l=0,int r=MAX)
{
    
    int m=(l+r)/2;
    bool left_border=f(cur,l)>f(lines[root],l);
    bool mid=f(cur,m)>f(lines[root],m);
    
    if(mid){
        swap(lines[root],cur);
    }
    if(r-l==1) return;
    else if(left_border!=mid){
        addLine(cur,2*root,l,m);
    }
    else{
        addLine(cur,2*root+1,m,r);
    }
}

ll maximum(int x,int root=1,int l=0,int r=MAX)
{
    int mid=(l+r)/2;

    if(r-l==1){
        return f(lines[root],x);
    }
    if(x<mid){
        return max(f(lines[root],x),maximum(x,2*root,l,mid));
    }
    return max(f(lines[root],x),maximum(x,2*root+1,mid,r));
}

void addSegment(pt cur,int a,int b,int root=1,int l=0,int r=MAX)
{
    if(a>b) return;
    
    if(a==l && b==r){
        addLine(cur,root,l,r);
        return;
    }
    if(r-l==1) return;
    int mid=(l+r)/2;
    addSegment(cur,a,min(mid,b),2*root,l,mid);
    addSegment(cur,max(mid,a),b,2*root+1,mid,r);
}

