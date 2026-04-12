// Rabin-Karp (single pattern) with double mod hash.
// Finds all occurrences of pattern in text in O(n + m).

using ll = long long;

const ll MOD1 = 1000000007LL;
const ll MOD2 = 1000000009LL;
const ll BASE = 911382323LL;

vector<int> rabinKarp(const string &text, const string &pattern) {
    int n = (int)text.size();
    int m = (int)pattern.size();
    vector<int> arns;

    if (m == 0 || m > n) return arns;

    vector<ll> p1(n + 1, 1), p2(n + 1, 1);
    vector<ll> h1(n + 1, 0), h2(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        p1[i] = (p1[i - 1] * BASE) % MOD1;
        p2[i] = (p2[i - 1] * BASE) % MOD2;

        h1[i] = (h1[i - 1] * BASE + (unsigned char)text[i - 1] + 1) % MOD1;
        h2[i] = (h2[i - 1] * BASE + (unsigned char)text[i - 1] + 1) % MOD2;
    }

    ll ph1 = 0, ph2 = 0;
    for (char c : pattern) {
        ph1 = (ph1 * BASE + (unsigned char)c + 1) % MOD1;
        ph2 = (ph2 * BASE + (unsigned char)c + 1) % MOD2;
    }

    auto getHash = [&](int l, int r) {
        ll x1 = (h1[r + 1] - (h1[l] * p1[r - l + 1]) % MOD1 + MOD1) % MOD1;
        ll x2 = (h2[r + 1] - (h2[l] * p2[r - l + 1]) % MOD2 + MOD2) % MOD2;
        return pair<ll, ll>{x1, x2};
    };

    for (int i = 0; i + m - 1 < n; i++) {
        if (getHash(i, i + m - 1) == pair<ll, ll>{ph1, ph2}) {
            arns.push_back(i);
        }
    }

    return arns;
}

inline void solve() {
    string text, pattern;
    cin >> text >> pattern;

    vector<int> pos = rabinKarp(text, pattern);
    cout << pos.size() << endl;
    for (int i : pos) cout << i << " ";
    cout << endl;
}
