#define x real() 
#define y imag()
 
typedef long long ll;
typedef double T;
typedef complex<T> pt;
typedef vector<int> vec;
const ll mod=1e9+7;
const int MAX=2e5+3;

T cross(pt v,pt w){ return v.x*w.y-v.y*w.x;}
T norma(pt a){return a.x*a.x+a.y*a.y;}
//ascii https://elcodigoascii.com.ar/

bool half(pt p){
    assert(p.x!=0 || p.y!=0);
    return p.y>0 || (p.y==0 && p.x<0);
}

void polarSort(vector<pt> &v){
    sort(all(v),[](pt v,pt w){
        return make_tuple(half(v),0)<make_tuple(half(w),cross(v,w));
    });
}

void polarSortNorm(vector<pt> &v){
    sort(all(v),[](pt v,pt w){
        return make_tuple(half(v),0,norma(v))<make_tuple(half(w),cross(v,w),norma(w));
    });
}