const ll mod=1e9+7;
const ll limit=4e9;
//ascii https://elcodigoascii.com.ar/

int orientation(point a,point b,point c){
    ll ori=(b.y-c.y)*(b.x-a.x)-(b.y-a.y)*(b.x-c.x);
    if(ori==0) return 0;
    if(ori>0) return 1;
    return 2;
}

void getLastTwo(point &a,point &b,stack<point> &s)
{
    a=s.top();
    s.pop();
    b=s.top();
    s.pop();
}

void show(point a){
    cout<<a.x<<" "<<a.y<<endl;
}

//Graham scan
 
void solve(){
    int n; cin>>n;
    vector<point> puntos(n);
    FO(i,n){
        ll a,b; cin>>a>>b;
        puntos[i]=make_pair(a,b);
    }
    sort(all(puntos));
    //Lower Part
    stack<point> lower;
    FO(i,n)
    {
        if(lower.size()<2){
            lower.push(puntos[i]);
            continue;
        }
        point a,b;
        getLastTwo(a,b,lower);
        if(orientation(a,b,puntos[i])<2)
        {
            lower.push(b);
            lower.push(a);
            lower.push(puntos[i]);
        }
        else{
            lower.push(b);
            i--;
        }
    }
    stack<point> upper;
    for(int i=n-1;i>=0;i--)
    {
        if(upper.size()<2){
            upper.push(puntos[i]);
            continue;
        }
        point a,b;
        getLastTwo(a,b,upper);
        if(orientation(a,b,puntos[i])<2)
        {
            upper.push(b);
            upper.push(a);
            upper.push(puntos[i]);
        }
        else{
            upper.push(b);
            i++;
        }
    }

    set<point> res;

    while(!lower.empty()){
        res.insert(lower.top());
        lower.pop();
    }
    while(!upper.empty()){
        res.insert(upper.top());
        upper.pop();
    }
    cout<<res.size()<<endl;
    for(auto c:res) show(c);
}