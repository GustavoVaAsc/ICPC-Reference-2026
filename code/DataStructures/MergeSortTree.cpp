class MergeSortTree{
private:
    vector<vector<int>> segtree;
    int n;
    int d;
 
public:
    void build(vector<int> &a){
        n = a.size();
        d=1;
        while(d<n) d<<=1;
        segtree.assign(2*d, {0});
        for(int i=0; i<n; i++)
            segtree[d+i] = {a[i]};
        
        for(int i=d-1; i>=1; i--){
            segtree[i].resize(segtree[2*i].size() + segtree[2*i].size());
            merge(segtree[2*i].begin(),segtree[2*i].end(),
                  segtree[2*i+1].begin(), segtree[2*i+1].end(),
                  segtree[i].begin());
        }
            
    }
 
    int query(int l, int r, int x){
        l+=d;
        r+=d;
 
        int arns = 0;
        while(l<=r){
            if(l%2 == 1){
                arns += lower_bound(segtree[l].begin(), segtree[l].end(), x) - segtree[l].begin();
                l++;
            }
            if(r%2 == 0){
                arns += lower_bound(segtree[r].begin(), segtree[r].end(), x) - segtree[r].begin();
                r--;
            }
            l>>=1;
            r>>=1;
        }
        return arns;
    }
 
};
