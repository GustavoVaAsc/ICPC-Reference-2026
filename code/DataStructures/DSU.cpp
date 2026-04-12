class DisjointSets{
    private:
        vector<int> parents;
        vector<int> sizes;
        int components;
    public:
        DisjointSets(int size) : parents(size), sizes(size,1), components(size){
            for(int i=0; i<size; i++){parents[i] = i;}
        }

        int find(int x) {return parents[x] == x ? x : (parents[x] = find(parents[x]));}

        bool unite(int x, int y){
            int x_root = find(x);
            int y_root = find(y);

            if(x_root == y_root) {return false;}

            if(sizes[x_root] < sizes[y_root]) {swap(x_root,y_root);}
            sizes[x_root] += sizes[y_root];
            parents[y_root] = x_root;
            components--;
            return true;
        }

        vector<int> getAllComponentSizes(){
            map<int, int> component_sizes;
            for (int i = 0; i < parents.size(); ++i){
                int root = find(i);
                if (component_sizes.find(root) == component_sizes.end()){
                    component_sizes[root] = sizes[root];
                }
            }

            vector<int> result;
            for (auto& [root, size] : component_sizes) {
                result.push_back(size);
            }

            return result;
        }


        bool connected(int x, int y) { return find(x) == find(y);}
        int getSize(int x) {return sizes[find(x)];}
        int getComponents() const {return components;}
};