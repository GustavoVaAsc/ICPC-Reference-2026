enum QueryType{ MAX, NONE };
 
struct Query{
    QueryType type = NONE;
    ll val = 0;
};
 
template <typename T> class LazySegTree {
    private:
        const int n;
        vector<T> tree;
        vector<Query> lazy;
        
        void build(int v, int l, int r, const vector<T> &a){
            if(l==r) tree[v] = a[l];
            else{
                int m = (l+r)/2;
                build(2*v, l, m, a);
                build(2*v+1, m+1, r, a);
                tree[v] = max(tree[2*v], tree[2*v+1]);
            }
        }
 
        void apply(int v, int len, const Query &x){
            tree[v] += x.val;
            lazy[v].val += x.val;
            lazy[v].type = MAX;
        }
 
        void push(int v, int l, int r){
            int m = (l+r)/2;
            apply(2*v, m-l+1, lazy[v]);
            apply(2*v+1, r-m, lazy[v]);
            lazy[v] = Query();
        }
 
        void update(int v, int l, int r, int ql, int qr, const Query &x){
            if(qr < l or ql > r) return;
 
            if(ql<=l and r <= qr) apply(v,r-l+1,x);
            else{
                push(v,l,r);
                int m = (l+r)/2;
                update(2*v,l,m,ql,qr,x);
                update(2*v+1,m+1,r,ql,qr,x);
                tree[v] = max(tree[2*v], tree[2*v+1]);
            }
        }
 
        T query(int v, int l, int r, int ql, int qr){
            if(qr < l || ql > r) return LLONG_MIN;
            if(l>=ql and r<=qr) return tree[v];
            push(v,l,r);
            int m = (l+r)/2;
            
            return max(query(2*v, l, m, ql, qr), query(2*v+1,m+1,r,ql,qr));
        }
 
    public:
        LazySegTree(const vector<T> &a) : n(a.size()-1), tree(8 * (a.size()-1)), lazy(8 * (a.size()-1)){
            build(1, 0, n, a);
        }
 
        void update(int ql, int qr, const Query &x){
            update(1,0, n,ql,qr,x);
        }
 
        T query(int ql, int qr){ return query(1,0,n,ql,qr);};
 
};
