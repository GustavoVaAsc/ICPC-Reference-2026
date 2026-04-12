// Suffix Automaton
struct SuffixAutomaton {
    struct State {
        int link;
        int len;
        int next[26];

        State() : link(-1), len(0) {
            fill(next, next + 26, -1);
        }
    };

    vector<State> st;
    int last;

    SuffixAutomaton() {
        st.reserve(1);
        st.push_back(State());
        last = 0;
    }

    void extend(char ch) {
        int c = ch - 'a';

        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int)st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }

                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
    }

    void build(const string& s) {
        st.clear();
        st.push_back(State());
        last = 0;
        for (char ch : s) extend(ch);
    }

    // Number of distinct substrings of the built string.
    long long countDistinctSubstrings() const {
        long long ans = 0;
        for (int v = 1; v < (int)st.size(); v++) {
            ans += st[v].len - st[st[v].link].len;
        }
        return ans;
    }

    bool contains(const string& t) const {
        int v = 0;
        for (char ch : t) {
            int c = ch - 'a';
            if (st[v].next[c] == -1) return false;
            v = st[v].next[c];
        }
        return true;
    }
};

// Example of use:
long long distinctSubstringsIn(const string& s) {
    SuffixAutomaton sam;
    sam.build(s);
    return sam.countDistinctSubstrings();
}
