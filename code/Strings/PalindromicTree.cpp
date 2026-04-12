// Palindromic Tree (Eertree)
struct PalindromicTree {
    struct Node {
        int len;
        int link;
        int next[26];
        int occ; // occurrences as palindrome suffix while adding characters

        Node(int l = 0) : len(l), link(0), occ(0) {
            fill(next, next + 26, -1);
        }
    };

    vector<Node> tree;
    string s;
    int suff; // node of the longest suffix-palindrome of current string

    PalindromicTree() { init(); }

    void init() {
        tree.clear();
        tree.push_back(Node(-1)); // root 0: odd length root
        tree.push_back(Node(0));  // root 1: even length root
        tree[0].link = 0;
        tree[1].link = 0;
        s.clear();
        suff = 1;
    }

    int getLink(int v, int pos) const {
        while (true) {
            int curLen = tree[v].len;
            if (pos - 1 - curLen >= 0 && s[pos - 1 - curLen] == s[pos]) {
                return v;
            }
            v = tree[v].link;
        }
    }

    void addChar(char ch) {
        int c = ch - 'a';
        s.push_back(ch);
        int pos = (int)s.size() - 1;

        int cur = getLink(suff, pos);

        if (tree[cur].next[c] != -1) {
            suff = tree[cur].next[c];
            tree[suff].occ++;
            return;
        }

        int newNode = (int)tree.size();
        tree.push_back(Node(tree[cur].len + 2));
        tree[cur].next[c] = newNode;

        if (tree[newNode].len == 1) {
            tree[newNode].link = 1;
        } else {
            int linkCand = getLink(tree[cur].link, pos);
            tree[newNode].link = tree[linkCand].next[c];
        }

        suff = newNode;
        tree[suff].occ++;
    }

    void build(const string& str) {
        init();
        for (char ch : str) addChar(ch);
    }

    // Number of distinct palindromic substrings.
    int distinctPalindromes() const {
        return max(0, (int)tree.size() - 2);
    }
};

// Example of use:
int countDistinctPalindromes(const string& s) {
    PalindromicTree pt;
    pt.build(s);
    return pt.distinctPalindromes();
}
