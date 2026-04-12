class SegmentTree2D{
private:
    vector<vector<int>> segtree;
    int n;
    int m;
    int d1;
    int d2;
 
public:
 
    void build(vector<vector<int>> &a){
        n = a.size();
        m = a[0].size();
        d1=1;
        while(d1<n) d1<<=1;
        
        d2=1;
        while(d2<m) d2<<=1;
 
        segtree.assign(2*d1, vector<int>(2*d2,0));
 
        // Set leaves
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                segtree[d1+i][d2+j] = a[i][j];
        
        // Propagate on columns
        for(int i=d1; i<2*d1; i++){
            for(int j=d2-1; j>0; j--)
                segtree[i][j] = segtree[i][2*j] + segtree[i][2*j+1];
        }
 
        // Propagate on rows
        for(int i=d1-1; i>0; i--){
            for(int j=1; j<2*d2; j++)
                segtree[i][j] = segtree[2*i][j] + segtree[2*i+1][j];
        }
    }
 
    void update(int x, int y, int k){
        int r = x + d1;
        int c = y + d2;
 
        segtree[r][c] = k;
 
        // Update columns for the row corresponding to x
        for(int j=c>>1; j>0; j>>=1)
            segtree[r][j] = segtree[r][2*j] + segtree[r][2*j+1];
 
        
        for(int i=r>>1; i>0; i>>=1){
            segtree[i][c] = segtree[2*i][c] + segtree[2*i+1][c];
            for(int j=c>>1; j>0; j>>=1)
                segtree[i][j] = segtree[i][2*j] + segtree[i][2*j+1];
        }
    }
 
 
 
    int query(int x1, int y1, int x2, int y2){
        int lx = x1+d1, rx = x2+d1+1;
        
        ll arns = 0;
        while(lx<rx) {
            if(lx & 1){
                arns += query_y(lx, y1, y2);
                ++lx;
            }
            if (rx & 1){
                --rx;
                arns += query_y(rx, y1, y2);
            }
            lx >>= 1; rx >>= 1;
        }
        return arns;
    }
 
    int query_y(int row, int y1, int y2) {
        int ly = y1 + d2, ry = y2 + 1 + d2;
        int s = 0;
        while (ly < ry) {
            if(ly & 1) s+=segtree[row][ly++];
            if(ry & 1) s+=segtree[row][--ry];
            ly >>= 1; ry >>= 1;
        }
        return s;
    }
 
};
