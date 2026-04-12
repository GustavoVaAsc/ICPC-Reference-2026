vector<ull> h_map; 
vector<ull> t2_map;
vector<ull> d; // Random variable per depth
vector<vector<int>> tree;
vector<vector<int>> tree2;
int arns = 0;
 
ull mix(ull x){
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}
 
void init_rng(int depth){
    uint64_t seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937_64 rng(seed);
    d.resize(depth+1);
    for(int i=0; i<=depth; i++){
        d[i] = rng();
    }
}
 
void hash_tree1(int u, int prev, int depth){
    h_map[u] = 1;
    for(int v : tree[u]){
        if(v!=prev){
            hash_tree1(v,u,depth+1);
            h_map[u] += mix(h_map[v]) ; 
        }
    }
}
 
void hash_tree2(int u, int prev, int depth){
    t2_map[u] = 1;
    for(int v : tree2[u]){
        if(v!=prev){
            hash_tree2(v,u,depth+1);
        t2_map[u] += mix(t2_map[v]); 
        }
    }
}
