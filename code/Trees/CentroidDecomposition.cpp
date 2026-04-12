bool v[MAX];
int dst[MAX];
int sz[MAX];
vector<int> adj[MAX];        
 
// Buffer estatico global para recolectar profundidades rapidisimo
int depth_buffer[MAX];
 
class CentroidDecomposition {
    private:
        int k;
        ll res=0;
 
        void sztree(int s, int par=-1) {
            sz[s]=1;
            for(int ch : adj[s]){
                if(ch==par || v[ch]) continue;
                sztree(ch, s);
                sz[s] += sz[ch];
            }
        }
 
        // Un solo DFS por subarbol: guarda los resultados en el buffer continuo
        void get_depths(int s, int par, int depth, int &tail, int &max_d) {
            if(depth > k) return;
            depth_buffer[tail++] = depth;
            max_d = max(max_d, depth);
            for(int ch : adj[s]){
                if(ch==par || v[ch]) continue;
                get_depths(ch, s, depth+1, tail, max_d);
            }
        }
 
    public:
        CentroidDecomposition(int _k): k(_k) {
            res=0;
        }
 
        void addEdge(int a, int b){
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
 
        // VERSION ITERATIVA: A prueba de Stack Overflow (evita TLE/RTE en casos borde)
        int getCentroid(int s, int n) {
            int par = -1;
            bool found = true;
            while(found) {
                found = false;
                for(int ch : adj[s]) {
                    if(ch != par && !v[ch] && sz[ch] > n/2) {
                        par = s;
                        s = ch;
                        found = true;
                        break;
                    }
                }
            }
            return s;
        }
 
        void Decompose(int s, int par=-1) {
            sztree(s, par);
            s = getCentroid(s, sz[s]); // Encontramos centroide de forma segura
            v[s] = true;  
            
            dst[0] = 1;
            int current_max_depth = 0;
            sort(all(adj[s]),[](int a,int b){
                return sz[a]<sz[b];
            });
            
            for(int ch : adj[s]){
                if(v[ch]) continue; // Solo nos importa no cruzar componentes visitados
                
                int tail = 0;
                int sub_max_depth = 0;
                
                // 1. Recolectar (1 solo DFS)
                get_depths(ch, s, 1, tail, sub_max_depth);
                
                // 2. Contar caminos cruzados (bucle cache-friendly)
                for(int i = 0; i < tail; i++) {
                    res += dst[k - depth_buffer[i]];
                }
                
                // 3. Agregar subarbol actual al arreglo maestro
                for(int i = 0; i < tail; i++) {
                    dst[depth_buffer[i]]++;
                }
                
                current_max_depth = max(current_max_depth, sub_max_depth);
            }
            
            // Limpieza ultra rapida usando memset implicito
            fill(dst, dst + current_max_depth + 1, 0); 
            
            // Recursion para el resto de los componentes
            for(int ch : adj[s]){
                if(v[ch]) continue;
                Decompose(ch, s);
            }
        }
 
        ll getRes(){ return res; }
};