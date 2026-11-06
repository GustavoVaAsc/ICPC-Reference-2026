using ll = long long;
const int FSC_MOD = 1000000007;

// Fast Subset Convolution (O(n^2 * 2^n))
// For f, g on subsets of [0..n-1], computes h where:
// h[S] = sum_{T subset S} f[T] * g[S \ T]
// Main use cases:
// 1) DP on subsets where transition splits a mask into two disjoint parts.
// 2) Problems with subset partition contributions by disjoint union.

void addMod(int &a, int b) {
    a += b;
    if (a >= FSC_MOD) a -= FSC_MOD;
}

void subMod(int &a, int b) {
    a -= b;
    if (a < 0) a += FSC_MOD;
}

vector<int> fastSubsetConvolution(const vector<int> &f, const vector<int> &g, int n) {
    int N = 1 << n;
    vector<int> pop(N, 0);
    for (int m = 1; m < N; m++) pop[m] = pop[m >> 1] + (m & 1);

    vector<vector<int>> F(n + 1, vector<int>(N, 0));
    vector<vector<int>> G(n + 1, vector<int>(N, 0));

    for (int m = 0; m < N; m++) {
        F[pop[m]][m] = f[m];
        G[pop[m]][m] = g[m];
    }

    // SOS zeta transform over subsets for each popcount layer.
    for (int k = 0; k <= n; k++) {
        for (int bit = 0; bit < n; bit++) {
            for (int m = 0; m < N; m++) {
                if (m & (1 << bit)) {
                    addMod(F[k][m], F[k][m ^ (1 << bit)]);
                    addMod(G[k][m], G[k][m ^ (1 << bit)]);
                }
            }
        }
    }

    vector<vector<int>> H(n + 1, vector<int>(N, 0));
    for (int m = 0; m < N; m++) {
        for (int k = 0; k <= n; k++) {
            ll val = 0;
            for (int i = 0; i <= k; i++) {
                val += 1LL * F[i][m] * G[k - i][m];
                if (val >= (1LL << 62)) val %= FSC_MOD;
            }
            H[k][m] = (int)(val % FSC_MOD);
        }
    }

    // Inverse SOS (Mobius transform).
    for (int k = 0; k <= n; k++) {
        for (int bit = 0; bit < n; bit++) {
            for (int m = 0; m < N; m++) {
                if (m & (1 << bit)) {
                    subMod(H[k][m], H[k][m ^ (1 << bit)]);
                }
            }
        }
    }

    vector<int> h(N, 0);
    for (int m = 0; m < N; m++) h[m] = H[pop[m]][m];
    return h;
}

// Example of use:
// int n = ...;
// vector<int> f(1<<n), g(1<<n);
// vector<int> h = fastSubsetConvolution(f, g, n);
