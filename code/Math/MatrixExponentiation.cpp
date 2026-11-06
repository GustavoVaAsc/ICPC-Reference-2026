using ll = long long;

// Generic Matrix Exponentiation (mod M)
// Main use cases:
// 1) Linear recurrences (Fibonacci, k-step recurrences) in O(k^3 log n).
// 2) Count walks of length k in graphs using adjacency matrix powers.
// 3) Transition DP with fixed-size state transitions.

struct Matrix {
    int n;
    ll mod;
    vector<vector<ll>> a;

    Matrix(int n_, ll mod_, bool identity = false) : n(n_), mod(mod_), a(n_, vector<ll>(n_, 0)) {
        if (identity) {
            for (int i = 0; i < n; i++) a[i][i] = 1;
        }
    }

    static Matrix multiply(const Matrix& A, const Matrix& B) {
        Matrix C(A.n, A.mod, false);
        for (int i = 0; i < A.n; i++) {
            for (int k = 0; k < A.n; k++) {
                if (A.a[i][k] == 0) continue;
                for (int j = 0; j < A.n; j++) {
                    C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % A.mod;
                }
            }
        }
        return C;
    }

    static Matrix power(Matrix base, long long exp) {
        Matrix res(base.n, base.mod, true);
        while (exp > 0) {
            if (exp & 1LL) res = multiply(res, base);
            base = multiply(base, base);
            exp >>= 1LL;
        }
        return res;
    }
};

// Example use case 1: Fibonacci(n) mod MOD.
// [F(n+1)]   [1 1]^n [F(1)]
// [F(n)  ] = [1 0]   [F(0)]
ll fibonacciMatrix(long long n, ll MOD) {
    if (n == 0) return 0;
    Matrix T(2, MOD);
    T.a = {{1, 1}, {1, 0}};
    Matrix P = Matrix::power(T, n - 1);
    ll F1 = 1, F0 = 0;
    return (P.a[0][0] * F1 + P.a[0][1] * F0) % MOD;
}

// Contest note:
// For non-square transitions (state vectors), wrap the vector as Nx1 matrix.
