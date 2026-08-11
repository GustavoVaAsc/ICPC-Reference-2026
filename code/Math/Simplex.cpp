/**
 * Simplex algorithm for linear programming.
 * Solves max c*x subject to Ax <= b, x >= 0.
 * Uses two-phase simplex with Bland's rule for guaranteed termination.
 *
 * Usage:
 *   Simplex simplex(n);          // n = number of variables
 *   simplex.set_objective(c);    // c = objective coefficients
 *   simplex.add_constraint(a, b); // Ax <= b
 *   auto [max_val, solution] = simplex.solve();
 */

#include <bits/stdc++.h>
using namespace std;

const double INF = 1e100;
const double EPS = 1e-9;

struct Simplex {
    int n;                        // number of variables
    int m;                        // number of constraints
    vector<vector<double>> A;     // constraint matrix (m constraints, n variables)
    vector<double> b;             // RHS of constraints
    vector<double> c;             // objective coefficients

    Simplex(int n_) : n(n_), m(0), A(), b(), c(n_, 0.0) {}

    void set_objective(const vector<double>& c_) {
        c = c_;
    }

    void add_constraint(const vector<double>& a, double b_) {
        A.push_back(a);
        b.push_back(b_);
        m++;
    }

    pair<double, vector<double>> solve() {
        // Normalize: Ax <= b with b >= 0. If b < 0, multiply constraint by -1.
        for (int i = 0; i < m; i++) {
            if (b[i] < -EPS) {
                for (int j = 0; j < n; j++) A[i][j] = -A[i][j];
                b[i] = -b[i];
            }
        }

        // Two-phase simplex.
        // Phase 1: introduce artificial variables and find initial BFS.
        // Phase 2: solve original problem.

        // Variables: x[0..n-1] original, s[0..m-1] slack, a[0..m-1] artificial
        int N = n + m + m;
        int M = m;

        vector<vector<double>> T(M, vector<double>(N + 1, 0.0));

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < n; j++) T[i][j] = A[i][j];
            T[i][n + i] = 1.0;                              // slack
            T[i][n + m + i] = 1.0;                         // artificial
            T[i][N] = b[i];
        }

        // Phase 1 objective: minimize sum of artificial variables
        vector<double> obj(N + 1, 0.0);
        for (int i = 0; i < m; i++) obj[n + m + i] = 1.0;

        // Basic variables are artificial vars
        vector<int> basic(M);
        for (int i = 0; i < M; i++) basic[i] = n + m + i;

        // Eliminate artificial vars from objective row
        for (int i = 0; i < M; i++) {
            if (basic[i] >= n + m) {
                for (int j = 0; j <= N; j++) obj[j] -= T[i][j];
            }
        }

        // Run simplex on phase 1
        bool infeasible = !simplex_iterate(T, obj, basic, N, M);

        // Check feasibility: artificial vars must be zero
        double phase1_val = -obj[N];
        for (int i = 0; i < M; i++) phase1_val -= obj[basic[i]] * T[i][N];

        if (phase1_val > EPS || infeasible) {
            return {-INF, {}};
        }

        // Phase 2: build new tableau without artificial variables
        // Keep current BFS by carrying over basic variables
        int N2 = n + m;
        vector<vector<double>> T2(M, vector<double>(N2 + 1, 0.0));

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < n; j++) T2[i][j] = A[i][j];
            T2[i][n + i] = 1.0;
            T2[i][N2] = b[i];
        }

        // Determine new basic variables
        vector<int> basic2(M, -1);
        for (int i = 0; i < M; i++) {
            if (basic[i] < n + m) {
                basic2[i] = basic[i];
            }
        }

        // Pivot out artificial variables that are still basic
        for (int i = 0; i < M; i++) {
            if (basic2[i] == -1) {
                // Find a non-artificial variable to pivot in
                for (int j = 0; j < N2; j++) {
                    if (abs(T2[i][j]) > EPS) {
                        pivot(T2, basic2, i, j, M, N2);
                        break;
                    }
                }
            }
        }

        // Set up phase 2 objective
        vector<double> obj2(N2 + 1, 0.0);
        for (int j = 0; j < n; j++) obj2[j] = c[j];

        // Eliminate basic variables from objective
        for (int i = 0; i < M; i++) {
            if (basic2[i] != -1 && basic2[i] < N2) {
                double coeff = obj2[basic2[i]];
                if (abs(coeff) > EPS) {
                    for (int j = 0; j <= N2; j++) obj2[j] -= coeff * T2[i][j];
                }
            }
        }

        // Run simplex on phase 2
        bool unbounded = !simplex_iterate(T2, obj2, basic2, N2, M);

        if (unbounded) {
            return {INF, {}};
        }

        // Extract solution
        vector<double> x(n, 0.0);
        for (int i = 0; i < M; i++) {
            if (basic2[i] >= 0 && basic2[i] < n) {
                x[basic2[i]] = T2[i][N2];
            }
        }

        double max_val = -obj2[N2];
        for (int i = 0; i < M; i++) {
            if (basic2[i] >= 0) max_val -= obj2[basic2[i]] * T2[i][N2];
        }

        return {max_val, x};
    }

private:
    void pivot(vector<vector<double>>& T, vector<int>& basic, int row, int col, int m, int n) {
        double piv = T[row][col];
        if (abs(piv) < EPS) return;

        for (int j = 0; j <= n; j++) T[row][j] /= piv;
        for (int i = 0; i < m; i++) {
            if (i != row && abs(T[i][col]) > EPS) {
                double factor = T[i][col];
                for (int j = 0; j <= n; j++) T[i][j] -= factor * T[row][j];
            }
        }
        basic[row] = col;
    }

    bool simplex_iterate(vector<vector<double>>& T, vector<double>& obj, vector<int>& basic, int n, int m) {
        while (true) {
            // Bland's rule: entering variable is smallest index with negative reduced cost
            int entering = -1;
            for (int j = 0; j < n; j++) {
                if (obj[j] < -EPS) {
                    entering = j;
                    break;
                }
            }
            if (entering == -1) break;

            // Minimum ratio test with Bland's rule for leaving variable
            int leaving = -1;
            double min_ratio = INF;
            for (int i = 0; i < m; i++) {
                if (T[i][entering] > EPS) {
                    double ratio = T[i][n] / T[i][entering];
                    if (ratio < min_ratio - EPS || (abs(ratio - min_ratio) < EPS && basic[i] < basic[leaving])) {
                        min_ratio = ratio;
                        leaving = i;
                    }
                }
            }

            if (leaving == -1) return false; // unbounded

            pivot(T, basic, leaving, entering, m, n);

            double coeff = obj[entering];
            if (abs(coeff) > EPS) {
                for (int j = 0; j <= n; j++) obj[j] -= coeff * T[leaving][j];
            }
        }
        return true;
    }
};
