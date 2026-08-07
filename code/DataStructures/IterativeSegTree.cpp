class SegmentTree{
private:
    vector<int> segtree;
    int n;
    int d;
 
public:
 
    void build(vector<int> &a){
        n = a.size();
        d=1;
        while(d<n) d<<=1;
        segtree.assign(2*d, 0);
        for(int i=0; i<n; i++)
            segtree[d+i] = a[i];
        
        for(int i=d-1; i>=1; i--)
            segtree[i] = segtree[2*i] + segtree[2*i+1];
    }
 
    int find_first(int x){
        if(segtree[1]<x) return -1;
        int i=1;
 
        while(i<d){
            if(segtree[2*i] >= x) i = 2*i;
            else i = 2*i+1;
        }
 
 
        return i-d;
    }
 
    int find_kth(int x){
        //if(segtree[1]<x) return -1;
        int i=1;
 
        while(i<d){
            if(segtree[2*i] >= x) i = 2*i;
            else{
                x -= segtree[2*i];
                i = 2*i+1;
            } 
        }
        return i-d;
    }
 
 
    void update(int pos){
        pos+=d;
        segtree[pos] = 0; 
        
        while(pos>1){ 
            pos>>=1; 
            segtree[pos] = segtree[2*pos] + segtree[2*pos+1];
        }
    }
 
 
    int query(int l, int r){
        l+=d;
        r+=d;
 
        int mx = INT_MIN;
        while(l<=r){
            if(l%2 == 1) mx = max(mx, segtree[l++]);
            if(r%2 == 0) mx = max(mx, segtree[r--]);
            l>>=1;
            r>>=1;
        }
        return mx;
    }
 
};
