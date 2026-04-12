// Aho-Corasick Automaton (lowercase a-z)
struct AhoCorasick {
    static const int ALPH = 26;

    struct Node {
        int next[ALPH];
        int link;
        vector<int> out; // pattern ids ending here

        Node() : link(0) {
            fill(next, next + ALPH, -1);
        }
    };

    vector<Node> t;
    vector<int> patLen;

    AhoCorasick() { t.push_back(Node()); }

    int addString(const string& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) {
                t[v].next[c] = (int)t.size();
                t.push_back(Node());
            }
            v = t[v].next[c];
        }
        int id = (int)patLen.size();
        patLen.push_back((int)s.size());
        t[v].out.push_back(id);
        return id;
    }

    void build() {
        queue<int> q;

        for (int c = 0; c < ALPH; c++) {
            if (t[0].next[c] == -1) {
                t[0].next[c] = 0;
            } else {
                int u = t[0].next[c];
                t[u].link = 0;
                q.push(u);
            }
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int c = 0; c < ALPH; c++) {
                int u = t[v].next[c];
                if (u == -1) {
                    t[v].next[c] = t[t[v].link].next[c];
                    continue;
                }

                t[u].link = t[t[v].link].next[c];
                for (int id : t[t[u].link].out) t[u].out.push_back(id);
                q.push(u);
            }
        }
    }

    // Returns all matches as {ending_index_in_text, pattern_id}
    vector<pair<int, int>> findAll(const string& text) const {
        vector<pair<int, int>> ans;
        int v = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            int c = text[i] - 'a';
            v = t[v].next[c];
            for (int id : t[v].out) {
                ans.push_back({i, id});
            }
        }
        return ans;
    }
};

// Example of use:
// Count occurrences of each pattern in text.
vector<int> countPatternOccurrences(const string& text, const vector<string>& patterns) {
    AhoCorasick ac;
    for (const string& p : patterns) ac.addString(p);
    ac.build();

    vector<int> cnt(patterns.size(), 0);
    auto matches = ac.findAll(text);
    for (auto [endIdx, id] : matches) {
        (void)endIdx;
        cnt[id]++;
    }
    return cnt;
}
