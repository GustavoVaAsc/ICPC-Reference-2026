// XOR Hash for strings (very fast, collision-prone compared to polynomial hash).
// Good for randomized checks, grouping, and quick fingerprints.

using ull = unsigned long long;

mt19937_64 rng_xor((uint64_t)chrono::steady_clock::now().time_since_epoch().count());
array<ull, 256> H;

void initXorHash() {
    for (int i = 0; i < 256; i++) H[i] = rng_xor();
}

// Order-sensitive XOR hash with position mixing.
ull xorHash(const string &s) {
    ull arns = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        ull x = H[(unsigned char)s[i]];
        arns ^= (x + 0x9e3779b97f4a7c15ULL + (arns << 6) + (arns >> 2) + (ull)(i + 1));
    }
    return arns;
}

inline void solve() {
    initXorHash();

    int n; cin >> n;
    unordered_map<ull, int> freq;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        freq[xorHash(s)]++;
    }

    // Number of distinct hashes (not guaranteed distinct strings due to collisions).
    cout << (int)freq.size() << endl;
}
