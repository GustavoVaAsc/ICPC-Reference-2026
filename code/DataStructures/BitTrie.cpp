class Trie{
private:
    Trie *children[2];
    bool term_st; // is_end
 
    Trie* searchPrefix(int x){
        Trie* node = this;
 
        for(int i=29; i>=0; i--){
            int bit = (x>>i)&1;
            if(!node->children[bit]) return nullptr;
            node = node->children[bit];
        }
 
        return node;
    }
 
public:
    Trie() : term_st(false) {
        for(int i=0; i<2; i++)
            children[i] = nullptr;
    }
    
    void insert(int x) {
        Trie* node = this;
        for(int i=29; i>=0; i--){
            int bit = (x>>i)&1;
            if(!node->children[bit]) node->children[bit] = new Trie();
            node = node->children[bit];
        }
 
        node->term_st = true;
    }
    
    bool search(int x) {
        Trie* node = searchPrefix(x);
        return node != nullptr && node->term_st;
    }
    
    bool startsWith(int x) {
        Trie* node = searchPrefix(x);
        return node != nullptr;
    }
 
    int maxXor(int x){
        Trie* node = this;
        int arns = 0;
        for(int i=29; i>=0; i--){
            int bit = (x>>i)&1;
            int not_bit = 1-bit;
            if(node->children[not_bit]){
                arns|=(1<<i);
                node = node->children[not_bit];
            }else{
 
                node = node->children[bit];
            }
        }
 
        return arns;
    }
};