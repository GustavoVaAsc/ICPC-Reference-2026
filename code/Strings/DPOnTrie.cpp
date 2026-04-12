class Trie{
private:
    Trie *children[26];
    bool term_st; // is_end
 
    Trie* searchPrefix(const string &p){
        Trie* node = this;
 
        for(char c:p){
            int pos = c - 'a';
            if(!node->children[pos]) return nullptr;
            node = node->children[pos];
        }
        return node;
    }
 
public:
    Trie() : term_st(false) {
        for(int i=0; i<26; i++)
            children[i] = nullptr;
    }
    
    void insert(string word) {
        Trie* node = this;
        for(char c:word){
            int pos = c - 'a';
            if(!node->children[pos]) node->children[pos] = new Trie();
            node = node->children[pos];
        }
 
        node->term_st = true;
    }
    
    bool search(string word) {
        Trie* node = searchPrefix(word);
        return node != nullptr && node->term_st;
    }
    
    bool startsWith(string prefix) {
        Trie* node = searchPrefix(prefix);
        return node != nullptr;
    }
 
    int arnsDP(string s, int n){
        vector<int> dp(n+1, 0);
        // dp[i] -> ways to form the prefix s[0..i-1]
        dp[0] = 1;
 
        for(int i = 0; i < n; i++){
            Trie *it = this; // Iterate the Trie from the root
            for(int j = i; j < n; j++){
                int pos = s[j] - 'a';
                if(!it->children[pos]) break;
                it = it->children[pos];
 
                if(it->term_st)
                    dp[j+1] = (dp[j+1] + dp[i]) % MOD;
                
            }
        }
        return dp[n];
    }
};