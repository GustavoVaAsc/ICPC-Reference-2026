// Matrix exponentiation: A^n in O(k^3 log n) for kxk matrix.
// Templated on element type (ll, modint, etc.).

#include <vector>

template<class T>
struct Matrix {
    int n;
    std::vector<std::vector<T>> a;

    Matrix() {}
    Matrix(int _n, int _m, T val = T{}) : n(_n), a(_n, std::vector<T>(_m, val)) {}

    static Matrix identity(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; i++)
            res.a[i][i] = T{1};
        return res;
    }

    Matrix operator+(const Matrix& o) const {
        Matrix res(n, o.n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                res.a[i][j] = a[i][j] + o.a[i][j];
        return res;
    }

    Matrix operator*(const Matrix& o) const {
        int m = o.n;
        Matrix res(n, m);
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++) if (a[i][k] != T{})
                for (int j = 0; j < m; j++)
                    res.a[i][j] += a[i][k] * o.a[k][j];
        return res;
    }

    Matrix pow(long long e) const {
        Matrix res = identity(n);
        Matrix base = *this;
        while (e > 0) {
            if (e & 1) res = res * base;
            base = base * base;
            e >>= 1;
        }
        return res;
    }
};
