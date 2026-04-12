struct point{
    double x,y;
};

struct Vector{
    double a=0,b=0;
    void getVector(point p1,point p2){
        a=p2.x-p1.x;
        b=p2.y-p1.y;
    }

    double getModulo(){
        return pow(a*a+b*b,0.5);
    }

    Vector getUnitarian(){
        Vector x;
        x.a=a/getModulo();
        x.b=b/getModulo();
        //cout<<x.a<<" "<<x.b<<endl;
        return x;
    }

};

double dotProduct(Vector x,Vector y)
{
    return x.a*y.a+x.b*y.b;
}

double CrossProduct(Vector x,Vector y)
{
    return x.a*y.b-x.b*y.a;
}

inline void solve()
{
    
    point p1,p2,p3,p4;
    cin>>p1.x>>p1.y>>p2.x>>p2.y>>p3.x>>p3.y;
    Vector u,v,t;
    u.getVector(p1,p3);
    //cout<<u.a<<" "<<u.b<<endl;
    v.getVector(p2,p3);
    if(CrossProduct(u,v)>0) cout<<"LEFT"<<endl;
    else if(CrossProduct(u,v)<0) cout<<"RIGHT"<<endl;
    else cout<<"TOUCH"<<endl;
    
}
