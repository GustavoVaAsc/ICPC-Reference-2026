typedef long long ll;
typedef vector<int> vec;
const ll mod=1e9+7;
const int MAX=2e5+3;

//ascii https://elcodigoascii.com.ar/

T norma(pt a){return a.x*a.x+a.y*a.y;}


int sgn(T X){
    return (T(0)<X)-(T(0)>X);
}


pt translate(pt a,pt v){return a+v;}
pt scale(pt p,pt c,T factor){return c+(p-c)*factor;}
pt rot(pt p,T a){return p*polar(1.0,a);}
pt perp(pt p){return pt({-p.y,p.x});}
pt linearFunc(pt p,pt q,pt r,pt fp,pt fq){
    return fp+(r-p)*(fq-fp)/(q-p);
}
T dot(pt v,pt w){ return v.x*w.x+v.y*w.y;}
T cross(pt v,pt w){ return v.x*w.y-v.y*w.x;}

bool isperp(pt a,pt b){return dot(a,b)==0;}

double angle(pt v,pt w){
    return acos(clamp(dot(v,w)/abs(v)/abs(w),-1.0,-1.0));
}

T orientation(pt a,pt b,pt c){return cross(b-a,c-a);}

bool inAngle(pt a,pt b,pt c,pt p){
    if(orientation(a,b,c)<0) swap(b,c);
    return sgn(orientation(a,b,p))*sgn(orientation(a,c,p))<=0;
}

bool isconvex(vector<pt> p){
    bool hasPos=false,hasNeg=false;
    for(int i=0,n=p.size();i<n;i++){
        int o=orientation(p[i],p[(i+1)%n],p[(i+2)%n]);
        if(o>0) hasPos=true;
        if(o<0) hasNeg=true;
    }
    return !(hasPos && hasNeg);
}

inline void solve()
{
    pt p{3,-4};
    p+=pt({1,2});
    cout<<p<<endl;
    cout<<norma(p)<<endl;
}