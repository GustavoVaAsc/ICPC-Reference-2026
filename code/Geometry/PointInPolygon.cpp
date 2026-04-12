\begin{lstlisting}[style=compactcpp]
struct point{
    ll x,y;
    void show(){
        cout<<x<<" "<<y<<endl;
    }
};

int sign(ll a){
    if(a<0) return -1;
    if(a==0) return 0;
    if(a>0) return 1;
}

int signCP(point p,point p1,point p2)
{
    return sign(1LL*((p1.x-p.x)*(p2.y-p.y)-(p1.y-p.y)*(p2.x-p.x)));
}

bool intersect(point n, point m,point a,point b)
{
    if(signCP(n,a,b)*signCP(m,a,b)>0) return false;
    if(signCP(a,n,m)*signCP(b,n,m)>0) return false;
    return true;
}

bool inside(point a,point b,point c){
    return a.x>=min(b.x,c.x) && a.x<=max(b.x,c.x) && a.y>=min(b.y,c.y)
    && a.y<=max(b.y,c.y);
}

inline void solve()
{
    int n,m; cin>>n>>m;
    vector<point> vertices(n);
    FO(i,n)
    {
        cin>>vertices[i].x>>vertices[i].y;
    }
    point query,par,init,first,second;
    int counter;
    int resta=0;
    FO(i,m)
    {
        resta=0;
        counter=0;
        cin>>query.x>>query.y;
        par.x=query.x;
        par.y=-MAX-1;
        init.x=vertices[0].x;
        init.y=vertices[0].y;
        first.x=init.x;
        first.y=init.y;
        bool ver=false;
        for(int j=1;j<=n;j++)
        {
            second.x=vertices[j%n].x;
            second.y=vertices[j%n].y;
            point AB,u;
            AB.x=second.x-first.x;
            AB.y=second.y-first.y;
            u.x=second.x-query.x;
            u.y=second.y-query.y;
            if((AB.x*u.y-AB.y*u.x)==0 && inside(query,first,second)){
                cout<<"BOUNDARY"<<endl;
                ver=true;
                break;
            }
            if(intersect(query,par,first,second) && first.x<=query.x && query.x<second.x)
            {
                counter++;
            }
            if(intersect(query,par,first,second) && second.x<=query.x && query.x<first.x){
                counter++;
            }
            first.x=second.x;
            first.y=second.y;
        }
        point AB,u;
        AB.x=init.x-first.x;
        AB.y=init.y-first.y;
        u.x=init.x-query.x;
        u.y=init.y-query.y;
        if(!ver){
            //if(intersect(query,par,first,init)) counter++;
            if((counter)&1) cout<<"INSIDE";
            else cout<<"OUTSIDE";
            cout<<endl;
        }
    }
}