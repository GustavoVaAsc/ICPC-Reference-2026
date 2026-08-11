// Polynomial Operations class
// Supports +, -, *, /, %, eval, and interpolate over arbitrary type T
// Uses __int128 for safe multiplication and reduces mod 1e9+7 when needed

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;

template<typename T>
struct Poly {
    vector<T> a;

    // Constructors
    Poly() {}
    Poly(const vector<T>& v) : a(v) {}
    Poly(const T& scalar) : a(1, scalar) {}

    // Degree, -1 for zero polynomial
    int deg() const {
        return (int)a.size() - 1;
    }

    // Ensure no trailing zeros
    void normalize() {
        while (!a.empty() && a.back() == T(0)) a.pop_back();
    }

    // Coefficient access
    T& operator[](int i) { return a[i]; }
    const T& operator[](int i) const { return a[i]; }

    // Addition
    Poly operator+(const Poly& o) const {
        Poly res;
        res.a.resize(max(size(), o.size()));
        for (size_t i = 0; i < res.a.size(); i++) {
            T x = i < size() ? a[i] : T(0);
            T y = i < o.size() ? o.a[i] : T(0);
            res.a[i] = x + y;
        }
        res.normalize();
        return res;
    }

    // Subtraction
    Poly operator-(const Poly& o) const {
        Poly res;
        res.a.resize(max(size(), o.size()));
        for (size_t i = 0; i < res.a.size(); i++) {
            T x = i < size() ? a[i] : T(0);
            T y = i < o.size() ? o.a[i] : T(0);
            res.a[i] = x - y;
        }
        res.normalize();
        return res;
    }

    // Scalar multiplication
    Poly operator*(const T& scalar) const {
        Poly res;
        res.a.resize(size());
        for (size_t i = 0; i < size(); i++) {
            res.a[i] = a[i] * scalar;
        }
        res.normalize();
        return res;
    }

    // Polynomial multiplication using __int128 for intermediate results
    Poly operator*(const Poly& o) const {
        if (deg() < 0 || o.deg() < 0) return Poly();

        Poly res;
        res.a.resize(size() + o.size() - 1);
        for (size_t i = 0; i < size(); i++) {
            for (size_t j = 0; j < o.size(); j++) {
                __int128 prod = (__int128)a[i] * (__int128)o.a[j];
                ll prod_ll = (ll)(prod % MOD);
                res.a[i + j] = (T)((ll)res.a[i + j] + prod_ll);
                if (sizeof(T) != sizeof(ll)) {
                    // Keep values bounded for non-ll types
                    ll val = (ll)res.a[i + j] % MOD;
                    if (val < 0) val += MOD;
                    res.a[i + j] = (T)val;
                }
            }
        }
        res.normalize();
        return res;
    }

    // Division with remainder ( Euclidean division )
    // Returns quotient, remainder is stored in this object
    Poly divmod(const Poly& o, Poly& remainder) const {
        if (deg() < 0) {
            remainder = Poly();
            return Poly();
        }

        if (o.deg() < 0) {
            // Division by zero - should not happen in well-formed code
            remainder = *this;
            return Poly();
        }

        int n = deg();
        int m = o.deg();
        if (n < m) {
            remainder = *this;
            return Poly();
        }

        Poly q;
        q.a.resize(n - m + 1);
        remainder = *this;

        while (remainder.deg() >= m && remainder.deg() >= 0) {
            int d = remainder.deg() - m;
            T coef = remainder.a.back() / o.a.back();

            for (int i = 0; i <= m; i++) {
                remainder.a[d + i] = remainder.a[d + i] - coef * o.a[i];
            }
            q.a[d] = coef;
            remainder.normalize();
        }

        q.normalize();
        remainder.normalize();
        return q;
    }

    // Division operator (quotient only)
    Poly operator/(const Poly& o) const {
        Poly rem;
        return divmod(o, rem);
    }

    // Modulo operator (remainder only)
    Poly operator%(const Poly& o) const {
        Poly rem;
        divmod(o, rem);
        return rem;
    }

    // Evaluate polynomial at point x using Horner's method
    T eval(T x) const {
        if (deg() < 0) return T(0);
        T result = a.back();
        for (int i = deg() - 1; i >= 0; i--) {
            result = result * x + a[i];
        }
        return result;
    }

    // Interpolate: given xs and ys, find polynomial P such that P[xs[i]] = ys[i]
    // Uses Lagrange interpolation formula
    static Poly interpolate(const vector<T>& xs, const vector<T>& ys) {
        int n = xs.size();
        if (n == 0) return Poly();
        if (n == 1) return Poly(ys[0]);

        // Build Lagrange basis polynomials efficiently
        // Precompute prefix and suffix products
        vector<Poly> pref(n), suff(n);
        for (int i = 0; i < n; i++) {
            pref[i] = Poly({-xs[i], T(1)});
            suff[i] = Poly({-xs[i], T(1)});
        }
        for (int i = 1; i < n; i++) {
            pref[i] = pref[i] * pref[i - 1];
        }
        for (int i = n - 2; i >= 0; i--) {
            suff[i] = suff[i] * suff[i + 1];
        }

        Poly result;
        for (int i = 0; i < n; i++) {
            Poly num = (i == 0 ? Poly(T(1)) : pref[i - 1]) *
                       (i == n - 1 ? Poly(T(1)) : suff[i + 1]);

            // Compute denominator: prod_{j != i} (xs[i] - xs[j])
            T den = T(1);
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    den = den * (xs[i] - xs[j]);
                }
            }

            // L_i(x) = num(x) / den
            // We need to handle division - for integers mod MOD, use modular inverse
            // For general T, we assume den divides num evenly or T supports division
            Poly term = num * (ys[i] / den);
            result = result + term;
        }

        result.normalize();
        return result;
    }

    // Size helper
    size_t size() const { return a.size(); }
};

// Explicit template instantiations for common types
template struct Poly<ll>;
template struct Poly<int>;
template struct Poly<long double>;
template struct Poly<double>;

void solve() {
    // Example usage:
    // Polynomial addition, subtraction, multiplication
    Poly<ll> p1({1, 2, 3});       // 1 + 2x + 3x^2
    Poly<ll> p2({1, 1});          // 1 + x

    auto p3 = p1 + p2;            // 2 + 3x + 3x^2
    auto p4 = p1 - p2;            // 0 + 1x + 3x^2
    auto p5 = p1 * p2;            // (1 + 2x + 3x^2)(1 + x)

    // Division: p1 / p2 = quotient and remainder
    Poly<ll> rem;
    Poly<ll> q = p1.divmod(p2, rem);

    // Evaluation
    (void)p1.eval(ll(2));      // p1(2) = 1 + 4 + 12 = 17

    // Interpolation
    vector<ll> xs = {0, 1, 2};
    vector<ll> ys = {1, 3, 7};    // P(0)=1, P(1)=3, P(2)=7 -> P(x)=1+2x+x^2
    Poly<ll> interp = Poly<ll>::interpolate(xs, ys);
}
