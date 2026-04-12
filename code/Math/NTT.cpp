// Number Theoretic Transform (NTT)
// Usage: exact polynomial convolution under modulo arithmetic (no floating-point precision issues).
// Good for multiplying polynomials / counting ways where answers are required modulo MOD.
// Constraints: n must be a power of 2 and n <= ROOT_PW for this modulus/root setup.

const int MOD = 7340033;           // 7 * 2^20 + 1
const int ROOT = 5;                // primitive root for MOD
const int ROOT_INV = 4404020;      // inverse(ROOT) mod MOD
const int ROOT_PW = 1 << 20;       // max power-of-two supported

int binpow(int a, int b, int m = MOD) {
    int arns = 1;
    while (b > 0) {
        if (b & 1) arns = (int)(1LL * arns * a % m);
        a = (int)(1LL * a * a % m);
        b >>= 1;
    }
    return arns;
}

void ntt(vector<int> &a, bool invert) {
    int n = (int)a.size();

    // Bit-reversal permutation.
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? ROOT_INV : ROOT;
        for (int i = len; i < ROOT_PW; i <<= 1) {
            wlen = (int)(1LL * wlen * wlen % MOD);
        }

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j];
                int v = (int)(1LL * a[i + j + len / 2] * w % MOD);

                a[i + j] = u + v;
                if (a[i + j] >= MOD) a[i + j] -= MOD;

                a[i + j + len / 2] = u - v;
                if (a[i + j + len / 2] < 0) a[i + j + len / 2] += MOD;

                w = (int)(1LL * w * wlen % MOD);
            }
        }
    }

    if (invert) {
        int n_inv = binpow(n, MOD - 2, MOD);
        for (int &x : a) {
            x = (int)(1LL * x * n_inv % MOD);
        }
    }
}

// Polynomial multiplication modulo MOD with NTT.
vector<int> multiply_ntt(vector<int> a, vector<int> b) {
    int n = 1;
    while (n < (int)a.size() + (int)b.size() - 1) n <<= 1;

    // Must fit this NTT configuration. Use another modulus/CRT if larger needed.
    if (n > ROOT_PW) return {};

    a.resize(n);
    b.resize(n);

    ntt(a, false);
    ntt(b, false);

    for (int i = 0; i < n; i++) {
        a[i] = (int)(1LL * a[i] * b[i] % MOD);
    }

    ntt(a, true);
    return a;
}

void solve() {
    // Example usage:
    // Input two polynomials A (size n) and B (size m), output coefficients of A*B mod MOD.
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;

    vector<int> c = multiply_ntt(a, b);
    if (c.empty()) {
        // This means size exceeded ROOT_PW with current modulus configuration.
        return;
    }

    for (int i = 0; i < n + m - 1; i++) {
        cout << c[i] << " ";
    }
    cout << endl;
}